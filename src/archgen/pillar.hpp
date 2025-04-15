#ifndef PILLAR_H
#define PILLAR_H

#include "glm/ext/vector_float3.hpp"
#include <vector>

#include "../core/opengl_drawable.hpp"

class Pillar : public Drawable {
private:
    glm::vec3 loc; // LT
    float weight = 0.5;
public:
    Pillar(glm::vec3 loc) : Drawable() {
        this->loc = loc;

        std::vector<float> points = GeneratePoints();
        SetVertexes(points);
    }

    std::vector<float> GeneratePoints(){
        std::vector<glm::vec3> points;

        points.push_back({loc.x, 0, loc.z}); // A
        points.push_back({loc.x, 41, loc.z}); // B
        points.push_back({loc.x + weight, 0, loc.z}); // C

        points.push_back({loc.x, 41, loc.z}); // B
        points.push_back({loc.x + weight, 0, loc.z}); // C
        points.push_back({loc.x + weight, 41, loc.z}); // D

        points.push_back({loc.x, 0, loc.z + weight}); // E
        points.push_back({loc.x + weight, 0, loc.z + weight}); // F
        points.push_back({loc.x, 41, loc.z + weight}); // G

        points.push_back({loc.x + weight, 0, loc.z + weight}); // F
        points.push_back({loc.x, 41, loc.z + weight}); // G
        points.push_back({loc.x + weight, 41, loc.z + weight}); // H

        points.push_back({loc.x, 0, loc.z}); // A
        points.push_back({loc.x, 41, loc.z}); // B
        points.push_back({loc.x, 0, loc.z + weight}); // E

        points.push_back({loc.x, 41, loc.z}); // B
        points.push_back({loc.x, 0, loc.z + weight}); // E
        points.push_back({loc.x, 41, loc.z + weight}); // G

        points.push_back({loc.x + weight, 0, loc.z}); // C
        points.push_back({loc.x + weight, 41, loc.z}); // D
        points.push_back({loc.x + weight, 0, loc.z + weight}); // F

        points.push_back({loc.x + weight, 41, loc.z}); // D
        points.push_back({loc.x + weight, 0, loc.z + weight}); // F
        points.push_back({loc.x + weight, 41, loc.z + weight}); // H

        std::vector<float> results;

        for(glm::vec3 v : points){
            results.push_back(v.x);
            results.push_back(v.y);
            results.push_back(v.z);
            results.push_back(166.0f / 255.0f);
            results.push_back(166.0f / 255.0f);
            results.push_back(166.0f / 255.0f);
        }

        return results;
    }

};

#endif