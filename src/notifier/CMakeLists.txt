# src/notifier/CMakeLists.txt
add_library(notifier Notifier.cpp)

target_include_directories(notifier
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

enable_coverage(notifier)