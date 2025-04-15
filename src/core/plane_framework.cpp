#include <cstdlib>
#include <memory>

#include <spdlog/spdlog.h>

#include "plane_framework.hpp"
#include "opengl_glloader.hpp"
#include "opengl_shader.hpp"
#include "plane_drawable.hpp"

std::shared_ptr<Shader> PlaneFramework::shader = std::make_shared<Shader>();
std::shared_ptr<Camera> PlaneFramework::camera = std::make_shared<Camera>();
std::shared_ptr<Window> PlaneFramework::window = std::make_shared<Window>(camera);

void PlaneFramework::Init(){
    spdlog::info("PlaneFramework: Init Phase");
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
        
        drawable->Update(PlaneFramework::window);
        
        window->Draw();
    }
}

void PlaneFramework::Teardown(){
    spdlog::info("PlaneFramework: Teardown Phase");
    window->Teardown();
}