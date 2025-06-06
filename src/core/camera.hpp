#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "opengl_shader.hpp"
#include <memory>

class Camera {
private:
  glm::vec3 cameraPos =
      glm::vec3(10.0f, 0.05f, 10.0f); // 相機位置（上方往下看）
  glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f); // 世界的上方方向
  double yaw = -90.0f;
  double pitch = 0.0f;

public:
  glm::vec3 GetCameraPos() { return this->cameraPos; }
  glm::vec3 GetCameraFront() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return front;
  }
  glm::vec3 GetCameraUpVector() { return this->upVector; }
  double GetYaw() { return this->yaw; }
  double GetPitch() { return this->pitch; }
  void SetCameraPos(glm::vec3 cameraPos) { this->cameraPos = cameraPos; }
  void SetUpVector(glm::vec3 upVector) { this->upVector = upVector; }
  void SetYaw(double yaw) { this->yaw = yaw; }
  void SetPitch(double pitch) { this->pitch = pitch; }
  void SetValueToShader(std::shared_ptr<Shader> shader) {
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
    shader->SetUniformValue("projection", projection);

    glm::mat4 view =
        glm::lookAt(cameraPos, cameraPos + GetCameraFront(), upVector);
    shader->SetUniformValue("view", view);

    shader->SetUniformValue("ViewPos", this->cameraPos);
  }
};

#endif
