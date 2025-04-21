#include "archgen.hpp"
#include "glm/ext/vector_float3.hpp"
#include "ground.hpp"
#include "pillar.hpp"
#include "room_ground.hpp"
#include "cube.hpp"
#include <memory>

#define MOVE_UNIT 0.4

ArchGen::ArchGen() : IPlaneDrawable() {
    std::shared_ptr<Ground> ground = std::make_shared<Ground>();
    ground->InitVAO();

    std::shared_ptr<Pillar> pillar1 = std::make_shared<Pillar>(glm::vec3(5, 0, 5));
    pillar1->InitVAO();

    std::shared_ptr<Pillar> pillar2 = std::make_shared<Pillar>(glm::vec3(5, 0, 20));
    pillar2->InitVAO();

    std::shared_ptr<Pillar> pillar3 = std::make_shared<Pillar>(glm::vec3(20, 0, 20));
    pillar3->InitVAO();

    std::shared_ptr<Pillar> pillar4 = std::make_shared<Pillar>(glm::vec3(20, 0, 5));
    pillar4->InitVAO();

    std::shared_ptr<RoomGround> roomGround1 = std::make_shared<RoomGround>(
        glm::vec3(5, 0.005, 5), 
        glm::vec3(20.5, 0.005, 5), 
        glm::vec3(5, 0.005, 20.5),
        glm::vec3(20.5, 0.005, 20.5)
    );

    std::shared_ptr<RoomGround> roomGround4 = std::make_shared<RoomGround>(
        glm::vec3(5, 10.001, 5), 
        glm::vec3(20.5, 10.001, 5), 
        glm::vec3(5, 10.001, 20.5),
        glm::vec3(20.5, 10.001, 20.5)
    );
    
    std::shared_ptr<RoomGround> roomGround2 = std::make_shared<RoomGround>(
        glm::vec3(5, 20.001, 5), 
        glm::vec3(20.5, 20.001, 5), 
        glm::vec3(5, 20.001, 20.5),
        glm::vec3(20.5, 20.001, 20.5)
    );

    std::shared_ptr<RoomGround> roomGround5 = std::make_shared<RoomGround>(
        glm::vec3(5, 30.001, 5), 
        glm::vec3(20.5, 30.001, 5), 
        glm::vec3(5, 30.001, 20.5),
        glm::vec3(20.5, 30.001, 20.5)
    );

    std::shared_ptr<RoomGround> roomGround3 = std::make_shared<RoomGround>(
        glm::vec3(5, 40.001, 5), 
        glm::vec3(20.5, 40.001, 5), 
        glm::vec3(5, 40.001, 20.5),
        glm::vec3(20.5, 40.001, 20.5)
    );

    roomGround1->InitVAO();

    roomGround2->InitVAO();

    roomGround3->InitVAO();

    roomGround4->InitVAO();

    roomGround5->InitVAO();

    std::shared_ptr<Cube> cube1 = std::make_shared<Cube>(glm::vec3(5, 0, 5), glm::vec3(1, 1, 1));
    std::shared_ptr<Cube> cube2 = std::make_shared<Cube>(glm::vec3(10, 3, 10), glm::vec3(2, 5, 4));

    cube1->InitVAO();
    cube2->InitVAO();
   
    drawables.emplace("ground", ground);
    drawables.emplace("pillar1", pillar1);
    drawables.emplace("pillar2", pillar2);
    drawables.emplace("pillar3", pillar3);
    drawables.emplace("pillar4", pillar4);
    drawables.emplace("roomGround1", roomGround1);
    drawables.emplace("roomGround2", roomGround2);
    drawables.emplace("roomGround3", roomGround3);
    drawables.emplace("roomGround4", roomGround4);
    drawables.emplace("roomGround5", roomGround5);
    drawables.emplace("cube1", cube1);
    drawables.emplace("cube2", cube2);
  

}

void ArchGen::Update(std::shared_ptr<Window> window){

    for (auto& drawable : drawables) {
        drawable.second->Draw();
    }

    if(window->IsKeyPress(KEY_W)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        glm::vec3 cameraPos = camera->GetCameraPos();

        cameraPos += (float) MOVE_UNIT * camera->GetCameraFront();

        camera->SetCameraPos(cameraPos);
    }

    if(window->IsKeyPress(KEY_A)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        glm::vec3 cameraPos = camera->GetCameraPos();

        cameraPos -= glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUpVector())) * (float) MOVE_UNIT;

        camera->SetCameraPos(cameraPos);
    }

    if(window->IsKeyPress(KEY_D)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        glm::vec3 cameraPos = camera->GetCameraPos();

        cameraPos += glm::normalize(glm::cross(camera->GetCameraFront(), camera->GetCameraUpVector())) * (float) MOVE_UNIT;

        camera->SetCameraPos(cameraPos);
    }

    if(window->IsKeyPress(KEY_S)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        glm::vec3 cameraPos = camera->GetCameraPos();

        cameraPos -= (float) MOVE_UNIT * camera->GetCameraFront();

        camera->SetCameraPos(cameraPos);
    }

    if(window->IsKeyPress(KEY_SPACE)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        glm::vec3 cameraPos = camera->GetCameraPos();

        cameraPos.y += MOVE_UNIT;

        camera->SetCameraPos(cameraPos);
    }

    if(window->IsKeyPress(KEY_Z)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        glm::vec3 cameraPos = camera->GetCameraPos();

        cameraPos.y -= MOVE_UNIT;

        camera->SetCameraPos(cameraPos);
    }

    if(window->IsKeyPress(KEY_Q)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        double yaw = camera->GetYaw();

        yaw -= 1.0f;

        camera->SetYaw(yaw);
    }

    if(window->IsKeyPress(KEY_E)){
        std::shared_ptr<Camera> camera = window->GetCamera();
        double yaw = camera->GetYaw();

        yaw += 1.0f;

        camera->SetYaw(yaw);
    }
}

void ArchGen::Teardown(){
    for (auto& drawable : drawables) {
        drawable.second->Free();
    }
}
