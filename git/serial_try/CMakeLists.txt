cmake_minimum_required(VERSION 3.1)

project(serial_try)

add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}")

add_executable(main main.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(serial_lib)
add_subdirectory(serial_lib)
target_link_libraries(main serial_lib)
