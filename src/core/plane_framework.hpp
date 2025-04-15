#ifndef PLANE_FRAMEWORK_HPP
#define PLANE_FRAMEWORK_HPP

#include "camera.hpp"
#include "opengl_shader.hpp"
#include "opengl_window.hpp"
#include "plane_drawable.hpp"
#include <memory>

class PlaneFramework {
private:
    static std::shared_ptr<Window> window;
    static std::shared_ptr<Shader> shader;
    static std::shared_ptr<Camera> camera;
public:
    static void Init();
    static void Update(std::shared_ptr<IPlaneDrawable> drawable);
    static std::shared_ptr<Shader> GetShaderPtr() { return shader; }
    static void Teardown();
};

#endif