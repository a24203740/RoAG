#include "./core/plane_framework.hpp"
#include "./archgen/archgen.hpp"
#include <memory>

int main() {
    PlaneFramework::Init();
    auto archGen = std::make_shared<ArchGen>();
    PlaneFramework::Update(archGen);
    archGen->Teardown();
    PlaneFramework::Teardown();
}
