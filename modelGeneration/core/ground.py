import numpy
import shapely
from util import triangulate_shapely_polygon

class Ground:
    def __init__(self, outer: list[tuple[float, float]], inner: list[list[tuple[float, float]]], floor_z: float, height: float):
        self.outer = outer
        self.inner = inner
        self.height = height
        self.floor_z = floor_z
        
        self.base_polygon = None
        self.vertices = []
        self.faces = []
        
        self._process_point()
    
    def _convert_2d_to_3d(self, vertices_2d, height):
        vertices_3d = numpy.hstack([vertices_2d, numpy.full((len(vertices_2d), 1), height)])
        return vertices_3d
    
    def _process_vertices(self, vertices_2d):
        # convert 2D to 3D
        floor_vertices_3d = self._convert_2d_to_3d(vertices_2d, self.floor_z)
        roof_vertices_3d = self._convert_2d_to_3d(vertices_2d, self.height)
        
        # bring it together
        vertices = numpy.vstack([floor_vertices_3d, roof_vertices_3d])
        
        return vertices
        
    def _process_faces(self, faces):
        # x, y swap
        faces = faces[:, [1, 0, 2]]
        
        return numpy.vstack([faces, faces])
        
    def _process_point(self):
        if len(self.inner) > 0:
            base_polygon = shapely.geometry.Polygon(self.outer, self.inner)
        else:
            base_polygon = shapely.geometry.Polygon(self.outer)

        floor_vertices_2d, floor_faces, _ = triangulate_shapely_polygon(base_polygon)
        
        self.base_polygon = base_polygon
        self.vertices = self._process_vertices(floor_vertices_2d)
        self.faces = self._process_faces(floor_faces)
