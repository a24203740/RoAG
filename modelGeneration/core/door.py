import numpy

class Door:
    def __init__(self, x1, y1, x2, y2, h, b):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.h = h
        self.b = b

    def to_3D_coordinates(self):
        return numpy.array([[self.x1, self.y1, self.b], [self.x2, self.y2, self.b], [self.x2, self.y2, self.b + self.h], [self.x1, self.y1, self.b + self.h]])
