import numpy

class Wall:
    def __init__(self, x1, y1, x2, y2, z1, h):
        self.x1 = x1
        self.x2 = x2
        self.y1 = y1
        self.y2 = y2
        self.z1 = z1
        self.z2 = z1 + h
        
        self._process_vertices()
        self._process_faces()
        
    def _process_vertices(self):
        self.vertices = numpy.array([
            [self.x1, self.y1, self.z1],
            [self.x2, self.y2, self.z1],
            [self.x1, self.y1, self.z2],
            [self.x2, self.y2, self.z2],
        ])
        
    
    def _process_faces(self):
        faces = numpy.array([
            [0, 1, 2],
            [1, 3, 2],
        ])
        
        self.faces = faces
