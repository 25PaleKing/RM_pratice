cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Ofast -pthread -Wl,--no-as-needed" )

add_executable(main main.cpp)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}")

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(main 
${OpenCV_LIBS} 
fmt::fmt
)

# include_directories(serial_lib)
# add_subdirectory(serial_lib)
# target_link_libraries(main serial_lib)

include_directories(modules)
add_subdirectory(modules)
target_link_libraries(main modules)

include_directories(camera_lib)
add_subdirectory(camera_lib)
target_link_libraries(main camera_lib)
