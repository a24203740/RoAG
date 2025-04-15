#include "archgen.hpp"
#include "glm/ext/vector_float3.hpp"
#include "ground.hpp"
#include "pillar.hpp"
#include "room_ground.hpp"
#include <memory>

#define MOVE_UNIT 0.4

void ArchGen::Update(std::shared_ptr<Window> window){
    std::shared_ptr<Ground> ground = std::make_shared<Ground>();
    ground->Init();
    ground->Draw();

    std::shared_ptr<Pillar> pillar1 = std::make_shared<Pillar>(glm::vec3(5, 0, 5));
    pillar1->Init();
    pillar1->Draw();

    std::shared_ptr<Pillar> pillar2 = std::make_shared<Pillar>(glm::vec3(5, 0, 20));
    pillar2->Init();
    pillar2->Draw();

    std::shared_ptr<Pillar> pillar3 = std::make_shared<Pillar>(glm::vec3(20, 0, 20));
    pillar3->Init();
    pillar3->Draw();

    std::shared_ptr<Pillar> pillar4 = std::make_shared<Pillar>(glm::vec3(20, 0, 5));
    pillar4->Init();
    pillar4->Draw();

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

    roomGround1->Init();
    roomGround1->Draw();

    roomGround2->Init();
    roomGround2->Draw();

    roomGround3->Init();
    roomGround3->Draw();

    roomGround4->Init();
    roomGround4->Draw();

    roomGround5->Init();
    roomGround5->Draw();

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