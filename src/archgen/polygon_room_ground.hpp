#include "../core/opengl_drawable.hpp"
#include "earcut.hpp"

class PolygonRoomGround : public Drawable {
private:
  double y;
  std::vector<std::vector<std::array<double, 2>>> polygon;
  std::vector<std::array<double, 2>> vertexes;

public:
  PolygonRoomGround(std::vector<std::vector<std::array<double, 2>>> polygon,
                    double y)
      : polygon(polygon), y(y) {

    for (int i = 0; i < polygon.size(); i++) {
      for (int j = 0; j < polygon[i].size(); j++) {
        vertexes.push_back(polygon[i][j]);
      }
    }

    std::vector<float> points = GeneratePoints();
    std::vector<uint32_t> earcut_result = mapbox::earcut<uint32_t>(polygon);

    SetVertexes(points);
    SetAttributesLength({3, 3});
    SetIndices(earcut_result);
  }

  std::vector<float> GeneratePoints() {
    std::vector<float> results;

    for (int index = 0; index < vertexes.size(); index++) {
      results.push_back(std::get<0>(vertexes[index]));
      results.push_back(y);
      results.push_back(std::get<1>(vertexes[index]));
      results.push_back(45.0f / 255.0f);
      results.push_back(45.0f / 255.0f);
      results.push_back(45.0f / 255.0f);
    }

    return results;
  }
};