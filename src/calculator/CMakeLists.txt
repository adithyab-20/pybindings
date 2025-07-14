# src/calculator/CMakeLists.txt
add_library(calculator Calculator.cpp)

# Set the include directory for this component so that users of the library
# can include its headers
target_include_directories(calculator
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

enable_coverage(calculator)