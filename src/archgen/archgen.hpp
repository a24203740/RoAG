#include "../core/plane_drawable.hpp"
#include "../core/opengl_drawable.hpp"
#include <unordered_map>

class ArchGen : public IPlaneDrawable {
private:
  std::unordered_map<std::string, std::shared_ptr<Drawable>> drawables;
public:
    ArchGen();
    virtual void Update(std::shared_ptr<Window> window);
};
