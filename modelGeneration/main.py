import json

from shapely.geometry import LinearRing, Polygon

from core.model import Model
from core.ground import Ground
from core.wall import Wall
from core.walls import Walls

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
            model.add_wall(wall)
            
        floor_z += height

    model.export_obj("building.obj")
    print("Exported as building.obj")
