#ifndef ROOM_GROUND_HPP
#define ROOM_GROUND_HPP

#include "../core/opengl_drawable.hpp"

class RoomGround : public Drawable {
    glm::vec3 pA, pB, pC, pD;
public:
    RoomGround(glm::vec3 pA, glm::vec3 pB, glm::vec3 pC, glm::vec3 pD) : pA(pA), pB(pB), pC(pC), pD(pD) {
        std::vector<float> points = GeneratePoints();
        SetVertexes(points);   
    }

    std::vector<float> GeneratePoints(){
        std::vector<glm::vec3> points;

        points.push_back(pA); // A
        points.push_back(pB); // B
        points.push_back(pC); // C

        points.push_back(pB); // B
        points.push_back(pC); // C
        points.push_back(pD); // D

        std::vector<float> results;

        for(glm::vec3 v : points){
            results.push_back(v.x);
            results.push_back(v.y);
            results.push_back(v.z);
            results.push_back(45.0f / 255.0f);
            results.push_back(45.0f / 255.0f);
            results.push_back(45.0f / 255.0f);
        }

        return results;
    }
};

#endif