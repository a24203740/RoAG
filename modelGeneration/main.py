import json

from core.model import Model
from core.ground import Ground
from core.wall import Wall
from util import generate_wall_by_vertices

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
        walls: list[Wall] = []
        height: float = floor["height"]
        
        if floor["enable"] == False:
            continue

        ground = Ground(outer, inter, floor_z, height)
        model.add_ground(ground)

        walls += generate_wall_by_vertices(
            list(ground.base_polygon.exterior.coords), offset_dist, floor_z, height
        )

        for interiors in ground.base_polygon.interiors:
            walls += generate_wall_by_vertices(
                list(interiors.coords), offset_dist, floor_z, height
            )

        for room in floor["rooms"]:
            walls += generate_wall_by_vertices(
                [[point[0], point[1]] for point in room], offset_dist, floor_z, height
            )

        for wall in walls:
            model.add_wall(wall)
            
        floor_z += height

    model.export_obj("building.obj")
    print("Exported as building.obj")
