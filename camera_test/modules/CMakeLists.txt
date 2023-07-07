set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(detect detect_src)

add_library(modules SHARED ${detect_src})

target_link_libraries(
    modules
    fmt::fmt
    ${OpenCV_LIBS}
)