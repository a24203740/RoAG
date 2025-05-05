import shapely.geometry
import shapely.ops
import pyclipper
import triangle as tr
import trimesh
import numpy as np
from trimesh.visual import material, texture

def triangulate_shapely_polygon(poly):
    """Triangulate polygon with holes using triangle library."""
    assert isinstance(poly, shapely.geometry.Polygon)

    coords = list(poly.exterior.coords)
    segments = [(i, i + 1) for i in range(len(coords) - 1)]

    holes = []
    for interior in poly.interiors:
        hole_coords = list(interior.coords)
        start_index = len(coords)
        coords.extend(hole_coords)
        segments.extend((i, i + 1) for i in range(start_index, start_index + len(hole_coords) - 1))
        holes.append(np.mean(hole_coords[:-1], axis=0))

    coords = np.array(coords)
    data = {
        'vertices': coords,
        'segments': np.array(segments),
    }
    if holes:
        data['holes'] = np.array(holes)

    t = tr.triangulate(data, 'p')
    return t['vertices'], t['triangles'], t['holes']


def offset_polygon(floor_vertices, dist):
    pc = pyclipper.PyclipperOffset()
    path = pyclipper.scale_to_clipper(floor_vertices)
    pc.AddPath(path, pyclipper.JT_MITER, pyclipper.ET_CLOSEDPOLYGON)
    offset_paths = pc.Execute(pyclipper.scale_to_clipper(dist))
    return [pyclipper.scale_from_clipper(path) for path in offset_paths]


def create_wall_quads(rings, z0, z1):
    quads = []
    for ring in rings:
        verts = ring.coords
        for i in range(len(verts) - 1):
            p0 = np.array([verts[i][0], verts[i][1], z0])
            p1 = np.array([verts[i + 1][0], verts[i + 1][1], z0])
            p2 = np.array([verts[i + 1][0], verts[i + 1][1], z1])
            p3 = np.array([verts[i][0], verts[i][1], z1])
            # quads.append([p0, p1, p2])
            # quads.append([p2, p3, p0])
            quads.append([p1, p0, p2])
            quads.append([p3, p2, p0])
    return quads

def create_wall_bottom(poly: shapely.geometry.Polygon) -> list[shapely.geometry.Polygon]:
    walls = []
    # exterior is linearloop of polygon outmost edge
    # interior is linearloop of polygon holes
    # coords is vertices of the linearloop
    outer_base = list(poly.exterior.coords)
    outer_offset = offset_polygon(poly.exterior.coords, -offset_dist)  # inward
    walls.append(shapely.geometry.Polygon(outer_base, outer_offset))

    for interior in poly.interiors:
        inner_base = list(interior.coords)
        inner_offset = offset_polygon(interior.coords, offset_dist)[0]  # outward
        walls.append(shapely.geometry.Polygon(inner_offset, [inner_base]))

    wall_bottom = shapely.set_operations.unary_union(walls)
    wall_bottoms = []
    if wall_bottom.geom_type == "MultiPolygon":
        assert(type(wall_bottom) is shapely.geometry.MultiPolygon)
        # if there are multiple polygons, we need to merge them
        for wall in wall_bottom.geoms:
            wall_bottoms.append(wall)
    elif wall_bottom.geom_type == "Polygon":
        assert(type(wall_bottom) is shapely.geometry.Polygon)
        wall_bottoms.append(wall_bottom)
    else:
        raise ValueError("Invalid geometry type: {}".format(wall_bottom.geom_type))
    return wall_bottoms

def generate_uvs_box_projection_with_tiling(mesh: trimesh.Trimesh, tile_scale=(1.0, 1.0)):
    """
    Generate UVs using a simple box projection and apply tiling.
    
    Args:
        mesh (trimesh.Trimesh): The input mesh.
        tile_scale (tuple): (tile_u, tile_v) repeat factor for UV tiling.
    
    Returns:
        trimesh.visual.texture.TextureVisuals: The textures
    """
    # Initialize UVs per vertex
    uvs = np.zeros((len(mesh.vertices), 2))

    # Compute per-face normals
    face_normals = mesh.face_normals
    axes = np.abs(face_normals)
    dominant_axis = np.argmax(axes, axis=1)

    # Temporary storage to avoid overwriting UVs for shared vertices
    uv_accum = [[] for _ in range(len(mesh.vertices))]

    for i, face in enumerate(mesh.faces):
        axis = dominant_axis[i]
        verts = mesh.vertices[face]

        if axis == 0:  # X-dominant → project on YZ
            uv = verts[:, [1, 2]]
        elif axis == 1:  # Y-dominant → project on XZ
            uv = verts[:, [0, 2]]
        else:  # Z-dominant → project on XY
            uv = verts[:, [0, 1]]

        # Normalize to 0–1 in local face UV space
        uv_min = uv.min(axis=0)
        uv_max = uv.max(axis=0)
        uv_range = np.maximum(uv_max - uv_min, 1e-6)
        uv_normalized = (uv - uv_min) / uv_range

        for j, v_idx in enumerate(face):
            uv_accum[v_idx].append(uv_normalized[j])

    # Average accumulated UVs for each vertex (simple blending for shared verts)
    for i in range(len(uvs)):
        if uv_accum[i]:
            uvs[i] = np.mean(uv_accum[i], axis=0)

    # Apply tiling
    uvs *= tile_scale

    # Assign UVs to mesh
    return texture.TextureVisuals(uv=uvs)


if __name__ == "__main__":
    floor_z = 0.0
    roof_z = 10.0
    offset_dist = 0.5  # half thickness (can do both inward and outward)

    outer = [(0, 0), (20, 0), (20, 15), (10, 20), (0, 15)]
    holes = [
        [(5.5, 2), (10.5, 2), (10.5, 7.25), (5.5, 7.25)],
    ]
    base_polygon = shapely.geometry.Polygon(outer, holes)
    # vertices is list of vertices, faces is indices of vertices
    floor_vertices_2d, floor_faces, holes_faces = triangulate_shapely_polygon(base_polygon)

    # add z dimension to vertices
    floor_vertices = np.hstack([floor_vertices_2d, np.full((len(floor_vertices_2d), 1), floor_z)])
    roof_vertices = np.hstack([floor_vertices_2d, np.full((len(floor_vertices_2d), 1), roof_z)])

    wall_vert_tuples = []
    wall_bottoms = create_wall_bottom(base_polygon)
    for wall_bottom in wall_bottoms:
        wall_vert_tuples.extend(create_wall_quads(shapely.get_rings(wall_bottom).tolist(), floor_z, roof_z))

    # combine to one mesh

    # Add floor and roof
    vertices = np.vstack([floor_vertices, roof_vertices])
    faces = []

    offset = 0
    faces.extend(floor_faces)
    # faces.extend(f + len(floor_vertices) for f in floor_faces)  # roof

    # Add wall triangles
    wall_faces = []
    for vert_tuple in wall_vert_tuples:
        start_index = len(vertices)
        vertices = np.vstack([vertices, vert_tuple])
        wall_faces.append([start_index, start_index + 1, start_index + 2])

    faces.extend(wall_faces)

    # Trimesh poressing and export

    mesh = trimesh.Trimesh(vertices=vertices, faces=faces, process=True)
    mesh.visual = generate_uvs_box_projection_with_tiling(mesh, tile_scale=(1.0, 1.0))
    print(mesh.visual.uv)
    mesh.export("building.obj", include_normals=True, include_texture=True, include_color=False)
    print("Exported as building.obj")
