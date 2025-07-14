#!/bin/bash
# This script should be run from the CMake build directory.

set -e
set -x

echo "--- Running tests to generate profile data ---"
# Use ctest to run all discovered tests.
# The LLVM_PROFILE_FILE pattern prevents race conditions between test runs.
cmake -E env LLVM_PROFILE_FILE="coverage_%p_%m.profraw" ctest

echo "--- Merging raw profile data ---"
llvm-profdata merge -sparse coverage_*.profraw -o coverage.profdata

echo "--- Generating unified HTML coverage report ---"
# Generate a single, unified report.
# The key is to pass the test EXECUTABLES to -object, not the libraries.
# We also ignore test files themselves to keep the report clean.
llvm-cov show -instr-profile=coverage.profdata -format=html -output-dir=coverage_html \
    -ignore-filename-regex=".*(tests|gtest|include/gtest).*" \
    -object bin/unit_test_calculator \
    -object bin/unit_test_logger \
    -object bin/unit_test_notifier \
    -object bin/integration_test_calculator_logger \
    -object bin/integration_test_logger_notifier \
    -object bin/e2e_test

echo "--- Coverage generation complete. Open build/coverage_html/index.html in a browser. ---"