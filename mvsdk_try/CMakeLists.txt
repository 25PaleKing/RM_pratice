cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mvsdk_try)

include_directories(camera_lib/camera)

add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}")

add_executable(main main.cpp)

include_directories(camera_lib)
add_subdirectory(camera_lib)
target_link_libraries(main camera_lib)
