import numpy

class Window:
    def __init__(self, x1, y1, x2, y2, y_offset, height, b):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.y_offset = y_offset
        self.height = height
        self.b = b
        
    def to_3D_coordinates(self):
        return numpy.array([[self.x1, self.y1, self.y_offset + self.b], [self.x2, self.y2, self.y_offset + self.b], [self.x2, self.y2, self.y_offset + self.b + self.height], [self.x1, self.y1, self.y_offset + self.b + self.height]])
