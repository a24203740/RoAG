#include <memory>
#include <spdlog/spdlog.h>

#include <glad/glad.h>

#include "opengl_window.hpp"

void Window::SetupWindowPerference(){
    glClearColor(135 / 255.0, 206 / 255.0, 235 / 255.0, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::Init(){
    spdlog::info("Window: Init Phase");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "ArchGen", NULL, NULL);

    if (window == NULL) {
        spdlog::error("Error: Create windows failed.");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Window::FrameBufferSizeCallback);

    this->window = window;
}