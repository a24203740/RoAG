#include "light.h"
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
    shader->SetUniformValue("lightSpaceMatrix", this->lightSpaceMatrixes[0]);
  } else if (this->mode == lightMode::POINT) {
    shader->SetUniformValue("light.mode", 1);
    shader->SetUniformValue("light.position", position);
    shader->SetUniformValue("farPlane", 25.0f);
  }
}

void Light::setShadowShaderUniform(Shader *shader) {
  if (this->mode == lightMode::ERROR) {
    spdlog::error("Light: Error light mode.");
    return;
  }
  if (this->mode == lightMode::DIRECTIONAL) {
    shader->SetUniformValue("lightSpaceMatrix", this->lightSpaceMatrixes[0]);
  } else if (this->mode == lightMode::POINT) {
    for (int i = 0; i < 6; ++i) {
      std::string name = "lightSpaceMatrix[" + std::to_string(i) + "]";
      shader->SetUniformValue(name, this->lightSpaceMatrixes[i]);
    }
    shader->SetUniformValue("lightPos", position);
    shader->SetUniformValue("farPlane", 25.0f);
  } else {
    spdlog::error("Light: Unsupported light mode for shadow mapping.");
    return;
  }
}
