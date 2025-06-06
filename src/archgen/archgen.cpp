#include "archgen.hpp"
#include "glm/ext/vector_float3.hpp"
#include "ground.hpp"
#include <memory>

#define MOVE_UNIT 0.4
#define FLOOR_LEVEL 2

ArchGen::ArchGen() : IPlaneDrawable() {
  const std::string objDir = "./assets/obj/";
  const std::string textureDir = "./assets/texture/";
  
  for (int level = 1; level <= FLOOR_LEVEL; level++) {
    string groundName = to_string(level) + "F_ground";
    string wallName = to_string(level) + "F_wall";
    std::shared_ptr<Object> ground = std::make_shared<Object>(objDir + groundName + ".obj");
    std::shared_ptr<Object> wall = std::make_shared<Object>(objDir + wallName + ".obj");
    ground->load_to_buffer();
    ground->load_texture(textureDir + "ground.jpg");
    wall->load_to_buffer();
    wall->load_texture(textureDir + "wall.jpg");
    objects.emplace(groundName, ground);
    objects.emplace(wallName, wall);
  }

  light = std::make_shared<Light>(glm::vec3(1.0), glm::vec3(1.0), glm::vec3(1.0),
                                  glm::vec3(0.0, 10.0, 3.0), Light::POINT);
}

void ArchGen::Update(std::shared_ptr<Window> window, std::shared_ptr<Shader> shader) {

  auto generate_normal_matrix = [](glm::mat4 model) -> glm::mat3 {
    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
    return normalMatrix;
  };
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
  model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  shader->SetUniformValue("model", model);
  shader->SetUniformValue("normalMatrix", generate_normal_matrix(glm::mat4(1.0f)));
  light->setShaderUniform(shader.get());
  for (auto &object : objects) {
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
