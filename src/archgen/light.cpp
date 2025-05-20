#include "light.h"
#include <spdlog/spdlog.h>

void Light::setShaderUniform(Shader* shader) {
  if(this->mode == lightMode::ERROR) {
    spdlog::error("Light: Error light mode.");
    return;
  }
  shader->SetUniformValue("light.ambient", ambient);
  shader->SetUniformValue("light.diffuse", diffuse);
  shader->SetUniformValue("light.specular", specular);

  if(this->mode == lightMode::DIRECTIONAL) {
    shader->SetUniformValue("light.mode", 0);
    shader->SetUniformValue("light.direction", direction);
  } else if (this->mode == lightMode::POINT) {
    shader->SetUniformValue("light.mode", 1);
    shader->SetUniformValue("light.position", position);
  }
}
