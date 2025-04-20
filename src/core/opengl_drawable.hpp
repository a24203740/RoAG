#ifndef OPENGL_DRAWABLE_HPP
#define OPENGL_DRAWABLE_HPP


#include <glm/glm.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"

#include "opengl_shader.hpp"
#include <memory>
#include <vector>

class Drawable {
private:
    std::vector<float> vertexes;
    unsigned int VAO, VBO1, VBO2;
    glm::mat4 transform;

public:
    Drawable() = default;
    Drawable(std::vector<float> vertexes) : vertexes(vertexes) {}
    void SetVertexes(std::vector<float> vertexes){
        this->vertexes = vertexes;
    }
    void SetTransform(glm::mat4 transform) {this->transform = transform;};
    void Init();
    void Draw();
    void Free();
};

#endif
