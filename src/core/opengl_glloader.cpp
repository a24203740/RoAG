#include <cstdlib>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "opengl_glloader.hpp"

void GLLoader::Init(){
    spdlog::info("GLLoader: Init Phase");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        exit(1);
    }
}