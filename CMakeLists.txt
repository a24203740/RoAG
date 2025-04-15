cmake_minimum_required(VERSION 3.27)

project(ArchGen)
set(GLFW_BUILD_WAYLAND 0)
set(CMAKE_CXX_STANDARD 14)
set(IGG_GLAD_GL_VERSION 4.6)
set(IGG_GLAD_DOWNLOAD OFF)

include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1 # or the version you want to use
)
FetchContent_MakeAvailable(spdlog)

add_subdirectory("src")
add_subdirectory("extra")