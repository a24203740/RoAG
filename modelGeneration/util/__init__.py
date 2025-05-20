import numpy
import shapely
import pyclipper
import triangle
from core.wall import Wall
from trimesh import Trimesh
from trimesh.visual import texture


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
        segments.extend(
            (i, i + 1) for i in range(start_index, start_index + len(hole_coords) - 1)
        )
        holes.append(numpy.mean(hole_coords[:-1], axis=0))

    coords = numpy.array(coords)
    data = {
        "vertices": coords,
        "segments": numpy.array(segments),
    }
    if holes:
        data["holes"] = numpy.array(holes)

    t = triangle.triangulate(data, "p")
    return t["vertices"], t["triangles"], t["holes"]


def generate_uvs_box_projection_with_tiling(mesh: Trimesh, tile_scale=(1.0, 1.0)):
    """
    Generate UVs using a simple box projection and apply tiling.

    Args:
        mesh (trimesh.Trimesh): The input mesh.
        tile_scale (tuple): (tile_u, tile_v) repeat factor for UV tiling.

    Returns:
        trimesh.visual.texture.TextureVisuals: The textures
    """
    # Initialize UVs per vertex
    uvs = numpy.zeros((len(mesh.vertices), 2))

    # Compute per-face normals
    face_normals = mesh.face_normals
    axes = numpy.abs(face_normals)
    dominant_axis = numpy.argmax(axes, axis=1)

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
        uv_range = numpy.maximum(uv_max - uv_min, 1e-6)
        uv_normalized = (uv - uv_min) / uv_range

        for j, v_idx in enumerate(face):
            uv_accum[v_idx].append(uv_normalized[j])

    # Average accumulated UVs for each vertex (simple blending for shared verts)
    for i in range(len(uvs)):
        if uv_accum[i]:
            uvs[i] = numpy.mean(uv_accum[i], axis=0)

    # Apply tiling
    uvs *= tile_scale

    # Assign UVs to mesh
    return texture.TextureVisuals(uv=uvs)


def offset_polygon(floor_vertices, dist):
    pc = pyclipper.PyclipperOffset()
    path = pyclipper.scale_to_clipper(floor_vertices)
    pc.AddPath(path, pyclipper.JT_MITER, pyclipper.ET_CLOSEDPOLYGON)
    offset_paths = pc.Execute(pyclipper.scale_to_clipper(dist))
    return [pyclipper.scale_from_clipper(path) for path in offset_paths]


# def generate_wall_by_vertices(
#     vertices: list[tuple[int, int]], offset_dist: float, floor_z: float, height: float
# ):
#     walls = []
#
#     inner_offset = offset_polygon(vertices, -offset_dist)[0]
#     inner_offset.append(inner_offset[0])
#
#     for i in range(len(inner_offset) - 1):
#         walls.append(
#             Wall(
#                 inner_offset[i][0],
#                 inner_offset[i][1],
#                 inner_offset[i + 1][0],
#                 inner_offset[i + 1][1],
#                 floor_z + height,
#             )
#         )
#
#     outer_offset = offset_polygon(vertices, offset_dist)[0]
#     outer_offset.append(outer_offset[0])
#
#     for i in range(len(outer_offset) - 1):
#         walls.append(
#             Wall(
#                 outer_offset[i][0],
#                 outer_offset[i][1],
#                 outer_offset[i + 1][0],
#                 outer_offset[i + 1][1],
#                 floor_z + height,
#             )
#         )
#
#     return walls
