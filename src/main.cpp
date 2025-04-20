#include "./core/plane_framework.hpp"
#include "./archgen/archgen.hpp"
#include <memory>

int main() {
    PlaneFramework::Init();
    PlaneFramework::Update(std::make_shared<ArchGen>());
    PlaneFramework::Teardown();
}
