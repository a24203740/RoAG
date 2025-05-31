#include <spdlog/spdlog.h>

#include "plane_framework.hpp"
#include "opengl_glloader.hpp"
#include "opengl_shader.hpp"
#include "plane_drawable.hpp"

std::shared_ptr<PlaneFramework> PlaneFramework::instance = nullptr;
std::shared_ptr<PlaneFramework> PlaneFramework::GetInstance() {
    if (instance == nullptr) {
      instance = std::shared_ptr<PlaneFramework>(new PlaneFramework());
    }
    return instance;
}
PlaneFramework::PlaneFramework() {
    spdlog::info("PlaneFramework: Constructor");
    shader = nullptr;
    camera = nullptr;
    window = nullptr;
}


void PlaneFramework::Init(){
    spdlog::info("PlaneFramework: Init Phase");
    shader = std::make_shared<Shader>();
    camera = std::make_shared<Camera>();
    window = std::make_shared<Window>(camera);
    window->Init();
    GLLoader::Init();
    shader->Init();
}

void PlaneFramework::Update(std::shared_ptr<IPlaneDrawable> drawable){
    spdlog::info("PlaneFramework: Update Phase");
    while(!window->IsWindowShouldClose()){
        window->SetupWindowPerference();
        shader->Use();

        camera->SetValueToShader(shader);
        
        drawable->Update(window, shader);
        
        window->Draw();
    }
}

void PlaneFramework::Teardown(){
    spdlog::info("PlaneFramework: Teardown Phase");
    window->Teardown();
}

