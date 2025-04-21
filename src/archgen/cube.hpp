#ifndef CUBE_H
#define CUBE_H

#include "glm/ext/vector_float3.hpp"

#include "../core/opengl_drawable.hpp"

class Cube : public Drawable {
private:
    glm::vec3 position;
    glm::vec3 size;
public:
    Cube();
    Cube(glm::vec3 position, glm::vec3 size);
    void generateVertices();
};

#endif
