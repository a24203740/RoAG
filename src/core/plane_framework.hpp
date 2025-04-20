#ifndef PLANE_FRAMEWORK_HPP
#define PLANE_FRAMEWORK_HPP

#include "camera.hpp"
#include "opengl_shader.hpp"
#include "opengl_window.hpp"
#include "plane_drawable.hpp"
#include <memory>

class PlaneFramework {
private:
    std::shared_ptr<Window> window;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Camera> camera;

    // singleton
    PlaneFramework();
    PlaneFramework(const PlaneFramework&) = delete;
    PlaneFramework& operator=(const PlaneFramework&) = delete;
    static std::shared_ptr<PlaneFramework> instance;
public: 
    static std::shared_ptr<PlaneFramework> GetInstance(); 
    void Init();
    void Update(std::shared_ptr<IPlaneDrawable> drawable);
    std::shared_ptr<Shader> GetShaderPtr() { return shader; }
    void Teardown();
};

#endif
