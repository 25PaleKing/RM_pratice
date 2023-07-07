SET(CMAKE_CXX_STANDARD_REQUIRED 11)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(camera camera_src)

add_library(camera_lib SHARED ${camera_src})

target_link_libraries(camera_lib 
    ${OpenCV_LIBS}
    fmt::fmt
    MVSDK
)