#include "../core/plane_drawable.hpp"

class ArchGen : public IPlaneDrawable {
public:
    ArchGen() = default;
    virtual void Update(std::shared_ptr<Window> window);
};