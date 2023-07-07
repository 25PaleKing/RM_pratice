set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
message("Opencv version is ${fmt_VERSION}")

aux_source_directory(serial serial_src)

add_library(serial_lib SHARED ${serial_src})

target_link_libraries(serial_lib 
${OpenCV_LIBS}
)