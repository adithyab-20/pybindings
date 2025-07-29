#!/bin/bash

# Build script for AB Python Calculator using scikit-build-core

set -e  # Exit on any error

echo "Building AB Python Calculator with scikit-build-core..."

# Clean previous builds
echo "Cleaning previous builds..."
rm -rf build/
rm -rf dist/
rm -rf *.egg-info/
find . -name "*.so" -delete
find . -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null || true

# Install in development mode using uv (following your project standards)
echo "Installing in development mode with uv..."
uv pip install -e .

echo "Build complete! You can now run:"
echo "  python -c 'from ab_py_calculator import Calculator; calc = Calculator(); print(calc.add(2, 3))'"
echo "  python example.py"
if [ -d tests ]; then echo "  pytest tests/"; fi