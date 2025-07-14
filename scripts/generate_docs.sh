#!/bin/bash
# This script should be run from the CMake build directory.

set -e
set -x

echo "--- Generating documentation with Doxygen ---"

# Generate the documentation
cmake --build . --target docs

echo "--- Documentation generation complete ---"
echo "--- Open build/docs/html/index.html in a browser to view the documentation ---"