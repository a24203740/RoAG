#include <spdlog/spdlog.h>

#include <glad/glad.h>
#ifdef __linux__
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif
#include "plane_framework.hpp"
#include "opengl_glloader.hpp"

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
    window->Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    GLLoader::Init();
    shader->Init();
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void PlaneFramework::Update(std::shared_ptr<IPlaneDrawable> drawable){
    spdlog::info("PlaneFramework: Update Phase");
    while(!window->IsWindowShouldClose()){
        window->SetupWindowPerference(WINDOW_WIDTH, WINDOW_HEIGHT);
        shader->Use();
      
        camera->UpdateCameraPosition();
        camera->SetValueToShader(shader, WINDOW_WIDTH, WINDOW_HEIGHT);
        
        drawable->Update(window, shader);
        
        window->Draw();
    }
}

void PlaneFramework::Teardown(){
    spdlog::info("PlaneFramework: Teardown Phase");
    window->Teardown();
}

