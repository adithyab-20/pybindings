#!/bin/bash
# Format all C++ source files using clang-format

set -e

echo "Formatting C++ source files..."

# Format headers and source files in src directory
find src/ -name "*.h" -o -name "*.hpp" -o -name "*.cpp" | while read -r file; do
    echo "Formatting: $file"
    clang-format -i "$file"
done

# Format main.cpp
if [ -f "main.cpp" ]; then
    echo "Formatting: main.cpp"
    clang-format -i main.cpp
fi

# Format test files
find tests/ -name "*.h" -o -name "*.hpp" -o -name "*.cpp" | while read -r file; do
    echo "Formatting: $file"
    clang-format -i "$file"
done

echo "Code formatting complete!"