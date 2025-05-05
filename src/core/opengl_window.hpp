#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "camera.hpp"
#include <GLFW/glfw3.h>
#include <memory>

enum Key {
    KEY_W = GLFW_KEY_W,
    KEY_A = GLFW_KEY_A,
    KEY_S = GLFW_KEY_S,
    KEY_D = GLFW_KEY_D,
    KEY_SPACE = GLFW_KEY_SPACE,
    KEY_Z = GLFW_KEY_Z,
    KEY_Q = GLFW_KEY_Q,
    KEY_E = GLFW_KEY_E,
    KEY_K = GLFW_KEY_K,
    KEY_J = GLFW_KEY_J,
};

class Window {
private:
    GLFWwindow* window;
    std::shared_ptr<Camera> camera;
    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
public:
    Window(std::shared_ptr<Camera> camera) : camera(camera){
        
    }
    void Init();
    bool IsWindowShouldClose() { return glfwWindowShouldClose(window); };
    void SetupWindowPerference();
    void Draw(){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::shared_ptr<Camera> GetCamera() {return camera;}
    bool IsKeyPress(Key key) {return glfwGetKey(this->window, key) == GLFW_PRESS; }
    void Teardown() { 
        glfwTerminate(); 
    };
};

#endif
