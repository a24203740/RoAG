#include "../core/plane_drawable.hpp"
#include "../core/opengl_drawable.hpp"
#include "../core/object.h"
#include <unordered_map>

class ArchGen : public IPlaneDrawable {
private:
    std::unordered_map<std::string, std::shared_ptr<Object>> objects;
    std::shared_ptr<Drawable> ground;
public:
    ArchGen();
    virtual void Update(std::shared_ptr<Window> window, std::shared_ptr<Shader> shader);
    virtual void Teardown();
};
