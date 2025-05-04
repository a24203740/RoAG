import shapely.geometry
import shapely.ops
import pyclipper
import triangle as tr
import trimesh
import numpy as np

# --- Step 1: Define base polygon with holes ---

outer = [(0, 0), (20, 0), (20, 15), (10, 20), (0, 15)]
holes = [
    [(0.25, 0.25), (5.25, 0.25), (5.25, 5.25), (0.25, 5.25)],
    [(5.5, 0.25), (10.5, 0.25), (10.5, 7.25), (5.5, 7.25)],
    [(10.75, 0.25), (19.75, 0.25), (19.75, 3.25), (10.75, 3.25)]
]
base_polygon = shapely.geometry.Polygon(outer, holes)
# base_polygon = shapely.geometry.Polygon(outer)

# --- Step 2: Triangulate floor and roof using triangle ---

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

floor_vertices_2d, floor_faces, holes_faces = triangulate_shapely_polygon(base_polygon)

# --- Step 3: Create 3D floor and roof ---

floor_z = 0.0
roof_z = 10.0

floor_vertices = np.hstack([floor_vertices_2d, np.full((len(floor_vertices_2d), 1), floor_z)])
roof_vertices = np.hstack([floor_vertices_2d, np.full((len(floor_vertices_2d), 1), roof_z)])

# --- Step 4: Generate walls using offset polygon ---

offset_dist = 0.25  # half thickness (can do both inward and outward)

def offset_polygon(floor_vertices, dist):
    pc = pyclipper.PyclipperOffset()
    path = pyclipper.scale_to_clipper(floor_vertices)
    pc.AddPath(path, pyclipper.JT_MITER, pyclipper.ET_CLOSEDPOLYGON)
    offset_paths = pc.Execute(pyclipper.scale_to_clipper(dist))
    return [pyclipper.scale_from_clipper(path) for path in offset_paths]

outer_base = list(base_polygon.exterior.coords)
outer_offset = offset_polygon(base_polygon.exterior.coords, -offset_dist)[0]  # inward
outer_offset.append(outer_offset[0])  # close the polygon

inner_base = []
inner_offset = []
for interior in base_polygon.interiors:
    inner_base.append(list(interior.coords))
    inner_offset.append(offset_polygon(interior.coords, offset_dist)[0])  # outward
    inner_offset[-1].append(inner_offset[-1][0])  # close the polygon

wall_quads = []

def create_wall_quads(outside, inside, z0, z1):
    quads = []
    for i in range(len(outside) - 1):
        p0 = np.array([outside[i][0], outside[i][1], z0])
        p1 = np.array([outside[i + 1][0], outside[i + 1][1], z0])
        p2 = np.array([outside[i + 1][0], outside[i + 1][1], z1])
        p3 = np.array([outside[i][0], outside[i][1], z1])
        quads.append([p0, p1, p2])
        quads.append([p2, p3, p0])
    for i in range(len(inside) - 1):
        p0 = np.array([inside[i][0], inside[i][1], z0])
        p1 = np.array([inside[i + 1][0], inside[i + 1][1], z0])
        p2 = np.array([inside[i + 1][0], inside[i + 1][1], z1])
        p3 = np.array([inside[i][0], inside[i][1], z1])
        quads.append([p0, p1, p2])
        quads.append([p2, p3, p0])
    wall_ceil_verticies_2d, wall_ceil_face, _ = triangulate_shapely_polygon(shapely.geometry.Polygon(outside, [inside]))
    wall_ceil_verticies = np.hstack([wall_ceil_verticies_2d, np.full((len(wall_ceil_verticies_2d), 1), z1)])
    for f in wall_ceil_face:
        quads.append([wall_ceil_verticies[f[0]], wall_ceil_verticies[f[1]], wall_ceil_verticies[f[2]]])

    return quads

outer_wall_faces = create_wall_quads(outer_base, outer_offset, floor_z, roof_z)
inner_wall_faces = []
for i in range(len(inner_base)):
    inner_wall_faces.extend(create_wall_quads(inner_base[i], inner_offset[i], floor_z, roof_z))
wall_faces = outer_wall_faces + inner_wall_faces

# --- Step 5: Combine all into one mesh ---

# Add floor and roof
vertices = np.vstack([floor_vertices, roof_vertices])
faces = []

offset = 0
faces.extend(floor_faces)
# faces.extend(f + len(floor_vertices) for f in floor_faces)  # roof

# Add wall triangles
wall_triangles = []
for tri in wall_faces:
    start_index = len(vertices)
    vertices = np.vstack([vertices, tri])
    wall_triangles.append([start_index, start_index + 1, start_index + 2])

faces.extend(wall_triangles)

# --- Step 6: Export as OBJ using trimesh ---

mesh = trimesh.Trimesh(vertices=vertices, faces=faces, process=True)
print(mesh.vertex_normals)
mesh.export("building.obj", include_normals=True, include_texture=False, include_color=False)
print("Exported as building.obj")

