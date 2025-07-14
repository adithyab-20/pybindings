cmake_minimum_required(VERSION 3.22)
# Add vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file"
)

project(ab_modules CXX)

cmake_policy(SET CMP0111 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add after CMAKE_CXX_STANDARD
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Add code coverage flags
option(ENABLE_COVERAGE "Enable coverage reporting for tests" OFF)

function(enable_coverage target)
    if(ENABLE_COVERAGE)
        message(STATUS "Enabling Clang-native coverage for target: ${target}")
        target_compile_options(${target} PRIVATE -fprofile-instr-generate -fcoverage-mapping -O0 -g)
        target_link_options(${target} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    endif()
endfunction()

# Find GTest package (vcpkg will provide this)
find_package(GTest CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories for each component.
add_subdirectory(src/calculator)
add_subdirectory(src/logger)
add_subdirectory(src/notifier)

# Main executable using main.cpp.
add_executable(ab_modules main.cpp)
target_link_libraries(ab_modules
    PRIVATE
        calculator
        logger
        notifier
)
enable_coverage(ab_modules)

# Enable testing.
enable_testing()
# Find GTest package (vcpkg will provide this)
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

# Helper function for adding tests
function(add_gtest name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE GTest::gtest GTest::gtest_main)
    gtest_discover_tests(${name})
    enable_coverage(${name})
endfunction()


# === Modular Tests ===
# Unit Tests
add_gtest(unit_test_calculator src/calculator/tests/test_calculator.cpp)
target_link_libraries(unit_test_calculator PRIVATE calculator)

add_gtest(unit_test_logger src/logger/tests/test_logger.cpp)
target_link_libraries(unit_test_logger PRIVATE logger)

add_gtest(unit_test_notifier src/notifier/tests/test_notifier.cpp)
target_link_libraries(unit_test_notifier PRIVATE notifier)

# Integration Tests
add_gtest(integration_test_calculator_logger tests/integration/test_calculator_logger.cpp)
target_link_libraries(integration_test_calculator_logger PRIVATE calculator logger)

add_gtest(integration_test_logger_notifier tests/integration/test_logger_notifier.cpp)
target_link_libraries(integration_test_logger_notifier PRIVATE logger notifier)

# E2E Tests
add_gtest(e2e_test tests/e2e/test_e2e.cpp)
target_link_libraries(e2e_test PRIVATE calculator logger notifier)


# === Coverage Target ===
if(ENABLE_COVERAGE)
    # Collect all test targets to create a dependency.
    set(ALL_TEST_TARGETS
        unit_test_calculator
        unit_test_logger
        unit_test_notifier
        integration_test_calculator_logger
        integration_test_logger_notifier
        e2e_test
    )

    add_custom_target(coverage
        COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/generate_coverage.sh
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report via script..."
        DEPENDS ${ALL_TEST_TARGETS}
    )
endif()

# === Documentation with Doxygen ===
find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    # Set Doxygen configuration variables
    set(DOXYGEN_PROJECT_NAME "AB Modules")
    set(DOXYGEN_PROJECT_BRIEF "A modular C++ project with Calculator, Logger, and Notifier components")
    set(DOXYGEN_PROJECT_VERSION ${PROJECT_VERSION})
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_INPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/main.cpp")
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE NO)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_HTML_OUTPUT html)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_SOURCE_DIR}/README.md)
    set(DOXYGEN_FILE_PATTERNS "*.cpp *.h *.hpp *.md")
    set(DOXYGEN_EXCLUDE_PATTERNS "*/tests/* */build/* */vcpkg/*")
    set(DOXYGEN_EXAMPLE_PATH ${CMAKE_SOURCE_DIR})
    set(DOXYGEN_EXAMPLE_PATTERNS "*.cpp *.h")
    set(DOXYGEN_EXAMPLE_RECURSIVE YES)

    # Configure Doxygen
    doxygen_add_docs(docs
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/README.md
        COMMENT "Generating API documentation with Doxygen"
    )

    # Add an alias for easier access
    add_custom_target(documentation DEPENDS docs)
endif()