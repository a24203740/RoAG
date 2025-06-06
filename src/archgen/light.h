#ifndef LIGHT_H
#define LIGHT_H
#include "../core/opengl_shader.hpp"
#include <glm/glm.hpp>

class Light {
public:
  enum lightMode { ERROR, DIRECTIONAL, POINT };

private:
  glm::vec3 position;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  glm::vec3 direction;
  lightMode mode;

public:
  void setup(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse,
             glm::vec3 specular, glm::vec3 direction) {
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->direction = direction;
  }
  Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        glm::vec3 posOrDir, lightMode mode) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    if (mode == DIRECTIONAL) {
      this->direction = posOrDir;
    } else if (mode == POINT) {
      this->position = posOrDir;
    }
    this->mode = mode;
  }
  Light() {
    this->ambient = glm::vec3(0.0f);
    this->diffuse = glm::vec3(0.0f);
    this->specular = glm::vec3(0.0f);
    this->position = glm::vec3(0.0f);
    this->direction = glm::vec3(0.0f);
    mode = ERROR;
  }
  void setShaderUniform(Shader* shader);
};

#endif // !LIGHT_H
