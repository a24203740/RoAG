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
    std::vector<unsigned int> indices;
    std::vector<unsigned int> attributesLength;
    unsigned int VAO;
    glm::mat4 transform;
    bool checkDataIsValid();
    bool init{false};
    unsigned int lengthOfSingleVertex();
public:
    Drawable() = default;
    Drawable(std::vector<float> vertexes, std::vector<unsigned int> indices, std::vector<unsigned int> attributesLength, glm::mat4 transform = glm::mat4(1.0f)) {
      SetVertexes(vertexes);
      SetIndices(indices);
      SetAttributesLength(attributesLength);
      SetTransform(transform);
    }
    void SetVertexes(std::vector<float> vertexes){
        this->vertexes = vertexes;
    }
    void SetIndices(std::vector<unsigned int> indices){
        this->indices = indices;
    }
    void SetAttributesLength(std::vector<unsigned int> attributesLength){
        this->attributesLength = attributesLength;
    }
    void SetTransform(glm::mat4 transform) {this->transform = transform;};
    void InitVAO();
    void Draw();
    void Free();
};

#endif
