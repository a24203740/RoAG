#include "light.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <spdlog/spdlog.h>

void Light::setShaderUniform(Shader *shader) {
  if (this->mode == lightMode::ERROR) {
    spdlog::error("Light: Error light mode.");
    return;
  }
  shader->SetUniformValue("light.ambient", ambient);
  shader->SetUniformValue("light.diffuse", diffuse);
  shader->SetUniformValue("light.specular", specular);

  if (this->mode == lightMode::DIRECTIONAL) {
    shader->SetUniformValue("light.mode", 0);
    shader->SetUniformValue("light.direction", direction);
  } else if (this->mode == lightMode::POINT) {
    shader->SetUniformValue("light.mode", 1);
    shader->SetUniformValue("light.position", position);
  }
  this->setShadowShaderUniform(shader, this->mode == lightMode::DIRECTIONAL);
}

void Light::setShadowShaderUniform(Shader *shader, bool isDirectional) {
  if (this->mode == lightMode::ERROR) {
    spdlog::error("Light: Error light mode.");
    return;
  }
  if (this->mode != lightMode::DIRECTIONAL && isDirectional) {
    spdlog::error(
        "Light: setShadowShaderUniform called with non-directional light.");
    return;
  }
  glm::mat4 lightProjection =
      glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
  glm::mat4 lightView =
      glm::lookAt(direction, glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 lightSpaceMatrix = lightProjection * lightView;
  shader->SetUniformValue("lightSpaceMatrix", lightSpaceMatrix);
}
