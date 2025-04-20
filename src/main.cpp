#include "./core/plane_framework.hpp"
#include "./archgen/archgen.hpp"
#include <memory>

int main() {
    auto planeFramework = PlaneFramework::GetInstance();
    planeFramework->Init();
    auto archGen = std::make_shared<ArchGen>();
    planeFramework->Update(archGen);
    archGen->Teardown();
    planeFramework->Teardown();
}
