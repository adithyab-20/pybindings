# src/logger/CMakeLists.txt
add_library(logger Logger.cpp)

target_include_directories(logger
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

enable_coverage(logger)