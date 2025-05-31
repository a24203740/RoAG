#include "archgen.hpp"
#include "glm/ext/vector_float3.hpp"
#include "ground.hpp"
#include <memory>

#define MOVE_UNIT 0.4
#define FLOOR_LEVEL 2

ArchGen::ArchGen() : IPlaneDrawable() {
  const std::string objDir = "./assets/obj/";
  const std::string textureDir = "./assets/texture/";
  const std::string groundTexture = textureDir + "ground.jpg";
  const std::string wallTexture = textureDir + "wall.jpg";
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
  for (int level = 1; level <= FLOOR_LEVEL; level++) {
    string groundName = to_string(level) + "F_ground";
    string wallName = to_string(level) + "F_wall";
    std::shared_ptr<Model> ground = std::make_shared<Model>(objDir + groundName + ".obj", groundTexture);
    std::shared_ptr<Model> wall = std::make_shared<Model>(objDir + wallName + ".obj", wallTexture);
    ground->SetModel(modelMatrix);
    wall->SetModel(modelMatrix);
    objects.emplace(groundName, ground);
    objects.emplace(wallName, wall);
  }

  light = std::make_shared<Light>(glm::vec3(1.0), glm::vec3(1.0), glm::vec3(1.0),
                                  glm::vec3(0.0, 10.0, 3.0), Light::POINT);
}

void ArchGen::Update(std::shared_ptr<Window> window, std::shared_ptr<Shader> shader) {

  light->setShaderUniform(shader.get());
  for (auto &object : objects) {
    object.second->setShaderUniform(shader.get());
    object.second->render();
  }

  if (window->IsKeyPress(KEY_W)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    glm::vec3 cameraPos = camera->GetCameraPos();

    cameraPos += (float)MOVE_UNIT * camera->GetCameraFront();

    camera->SetCameraPos(cameraPos);
  }

  if (window->IsKeyPress(KEY_A)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    glm::vec3 cameraPos = camera->GetCameraPos();

    cameraPos -= glm::normalize(glm::cross(camera->GetCameraFront(),
                                           camera->GetCameraUpVector())) *
                 (float)MOVE_UNIT;

    camera->SetCameraPos(cameraPos);
  }

  if (window->IsKeyPress(KEY_D)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    glm::vec3 cameraPos = camera->GetCameraPos();

    cameraPos += glm::normalize(glm::cross(camera->GetCameraFront(),
                                           camera->GetCameraUpVector())) *
                 (float)MOVE_UNIT;

    camera->SetCameraPos(cameraPos);
  }

  if (window->IsKeyPress(KEY_S)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    glm::vec3 cameraPos = camera->GetCameraPos();

    cameraPos -= (float)MOVE_UNIT * camera->GetCameraFront();

    camera->SetCameraPos(cameraPos);
  }

  if (window->IsKeyPress(KEY_SPACE)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    glm::vec3 cameraPos = camera->GetCameraPos();

    cameraPos.y += MOVE_UNIT;

    camera->SetCameraPos(cameraPos);
  }

  if (window->IsKeyPress(KEY_Z)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    glm::vec3 cameraPos = camera->GetCameraPos();

    cameraPos.y -= MOVE_UNIT;

    camera->SetCameraPos(cameraPos);
  }

  if (window->IsKeyPress(KEY_Q)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    double yaw = camera->GetYaw();

    yaw -= 1.0f;

    camera->SetYaw(yaw);
  }

  if (window->IsKeyPress(KEY_E)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    double yaw = camera->GetYaw();

    yaw += 1.0f;

    camera->SetYaw(yaw);
  }  
  if (window->IsKeyPress(KEY_K)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    double pitch = camera->GetPitch();

    pitch += 1.0f;

    camera->SetPitch(pitch);
  }
  if (window->IsKeyPress(KEY_J)) {
    std::shared_ptr<Camera> camera = window->GetCamera();
    double pitch = camera->GetPitch();

    pitch -= 1.0f;

    camera->SetPitch(pitch);
  }
}

void ArchGen::Teardown() {
}
