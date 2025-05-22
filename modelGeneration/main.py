import json

import numpy
from shapely.geometry import LinearRing, Polygon

from core.model import Model
from core.ground import Ground
from core.door import Door
from core.window import Window
from core.walls import Walls
from util import convert_doors_to_door_objects, convert_windows_to_window_objects, is_full_overlap

if __name__ == "__main__":
    floor_z = 0
    offset_dist = 0.5 / 2

    with open("model.json") as f:
        model_json = json.loads(f.read())

    basePolygon = model_json["basePolygon"]

    outer: list[tuple[float, float]] = [[point[0], point[1]] for point in basePolygon["outer"]]
    inter: list[tuple[float, float]] = [
        [[point[0], point[1]] for point in inter] for inter in basePolygon["inter"]
    ]

    model = Model()

    for floor in model_json["floors"]:
        height: float = floor["height"]
        doors = convert_doors_to_door_objects(floor["door"], height)
        windows = convert_windows_to_window_objects(floor["window"])

        print(doors)

        if floor["enable"] == False:
            continue

        ground = Ground(outer, inter, floor_z, height)
        assert type(ground.base_polygon) is Polygon
        model.add_ground(ground)

        walls = Walls()
        print ("ext")
        walls.wall_bottom_generation_from_ring(ground.base_polygon.exterior, offset_dist)

        for interiors in ground.base_polygon.interiors:
            print ("int")
            walls.wall_bottom_generation_from_ring(interiors, offset_dist)

        for room in floor["rooms"]:
            print ("room")
            ring = LinearRing(room)
            walls.wall_bottom_generation_from_ring(ring, offset_dist)

        walls_obj = walls.wall_generations_from_bottoms(floor_z, height)

        for wall in walls_obj:
            wall_coord = wall.get_non_offset_coord()
            
            if None not in wall_coord :        
                offset_diff = numpy.array(wall_coord) - numpy.array(wall.get_offset_coord())
                for door in doors:
                    if(not None in wall_coord and is_full_overlap(wall_coord[0], wall_coord[1], wall_coord[2], wall_coord[3], door.x1, door.y1, door.x2, door.y2)):
                        new_door = Door(door.x1 - offset_diff[0], door.y1 - offset_diff[1], door.x2 - offset_diff[2], door.y2 - offset_diff[3], height * 0.5)
                        wall.dig_a_hole(new_door.to_3D_coordinates())
                        
                for window in windows:
                    if(not None in wall_coord and is_full_overlap(wall_coord[0], wall_coord[1], wall_coord[2], wall_coord[3], window.x1, window.y1, window.x2, window.y2)):
                        new_window = Window(window.x1 - offset_diff[0], window.y1 - offset_diff[1], window.x2 - offset_diff[2], window.y2 - offset_diff[3], window.y_offset, window.height)
                        wall.dig_a_hole(new_window.to_3D_coordinates(), True)

            model.add_wall(wall)
            
        floor_z += height

    model.export_obj("building.obj")
    print("Exported as building.obj")
