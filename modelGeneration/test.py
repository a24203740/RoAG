import numpy
import trimesh
from shapely import Polygon

ORIGIN = numpy.array([0, 0, 0])
real_wall_3D_points = numpy.array([[360, 300, 0], [390, 300, 0], [390, 300, 140], [360, 300, 140]])
wall_3D_points = numpy.array([[10, 10, 0], [25, 25, 0], [25, 25, 20], [10, 10, 20]])
door_3D_points = numpy.array([[360, 300, 80], [390, 300, 80], [390, 300, 120], [360, 300, 120]])

def convert_to_2d(P, origin, u_axis, v_axis):
    rel = P - origin
    u = numpy.dot(rel, u_axis)
    v = numpy.dot(rel, v_axis)
    return numpy.array([u, v])

def convert_to_3d(uv, origin, u_axis, v_axis):
    return origin + uv[0] * u_axis + uv[1] * v_axis

def to_2D_points(origin, _3D_points, u_vec, v_vec):
    points_2d = numpy.array([convert_to_2d(p, origin, u_vec, v_vec) for p in _3D_points])

    return points_2d, u_vec, v_vec

origin = real_wall_3D_points[0]

u_vec = real_wall_3D_points[1] - origin
u_vec = u_vec / numpy.linalg.norm(u_vec)

w_vec = real_wall_3D_points[2] - origin

n_vec = numpy.cross(u_vec, w_vec)
n_vec = n_vec / numpy.linalg.norm(n_vec)

v_vec = numpy.cross(n_vec, u_vec)
v_vec = v_vec / numpy.linalg.norm(v_vec)

wall_2d, u_axis, v_axis = to_2D_points(origin, real_wall_3D_points, u_vec, v_vec)
door_2d, _, _ = to_2D_points(origin, door_3D_points, u_vec, v_vec)

wall_polygon = Polygon(shell=wall_2d)
door_polygon = Polygon(shell=door_2d)
wall_have_door_polygon: Polygon = wall_polygon.difference(door_polygon)

print(wall_2d)
print(door_2d)