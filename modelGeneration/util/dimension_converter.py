import numpy

ORIGIN = numpy.array([0, 0, 0])

def convert_to_2d(P, origin, u_axis, v_axis):
    rel = P - origin
    u = numpy.dot(rel, u_axis)
    v = numpy.dot(rel, v_axis)
    return numpy.array([u, v])

def convert_to_3d(uv, origin, u_axis, v_axis):
    return origin + uv[0] * u_axis + uv[1] * v_axis

def convert_3d_to_2d(origin: numpy.ndarray, coordinates_3d: numpy.ndarray, u_vec: numpy.ndarray, v_vec: numpy.ndarray):
    points_2d = numpy.array([convert_to_2d(p, origin, u_vec, v_vec) for p in coordinates_3d], dtype=float)

    return points_2d

def convert_2d_to_3d(origin: numpy.ndarray, coordinates_2d: numpy.ndarray, u_axis: numpy.ndarray, v_axis: numpy.ndarray):
    return numpy.array([
        convert_to_3d(uv, origin, u_axis, v_axis)
        for uv in coordinates_2d
    ])