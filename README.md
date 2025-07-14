# C++ Technology Template Repository

## Overview

This template serves as a foundation for designing and developing projects in C++, fully equipped for immediate use. It includes features for build management, unit testing, continuous integration, static analysis, code style adherence, automated documentation generation, and component specification.

## Prerequisites

Before building the project, ensure you have CMake and Ninja installed on your system. These tools are essential for configuring, building, and managing dependencies.

### Installing LLVM/Clang

This project requires the Clang compiler and related LLVM tools for compilation, static analysis, and code coverage:

* **Windows**: Download the LLVM installer from the LLVM Releases page. During installation, select the option to add LLVM to your system PATH.
* **macOS**: Install via Homebrew with `brew install llvm`. You may need to update your PATH to use the Homebrew-installed version instead of the system version.
* **Linux**: Install via package manager. For Ubuntu, you can use:
sudo apt-get install clang clang-tidy llvm

### Installing CMake

CMake is a cross-platform build system generator. To install CMake:

* **Windows**: Download the installer from the CMake Downloads page and follow the installation prompts. Ensure you select the option to add CMake to your system PATH.
* **macOS**: Use Homebrew by running `brew install cmake` in the terminal, or download the macOS binary from the CMake website.
* **Linux**: Most distributions include CMake in their package managers. For example, on Ubuntu, you can install it with `sudo apt-get install cmake`.

### Installing Ninja

Ninja is a small build system focused on speed. To install Ninja:

* **Windows**: Download the latest binary from Ninja's GitHub releases page. Extract the executable and add its location to your system's PATH.
* **macOS and Linux**: Ninja can be installed through Homebrew on macOS (`brew install ninja`) or through the package manager on Linux (for example, `sudo apt-get install ninja-build` on Ubuntu).

### Installing Doxygen (for Documentation)

Doxygen is used to generate project documentation from code comments:

* **Windows**: Download the installer from the Doxygen Downloads page.
* **macOS**: Install via Homebrew with `brew install doxygen graphviz`.
* **Linux**: Install via package manager, for example: `sudo apt-get install doxygen graphviz`.

## Project Setup and Build Instructions

This project uses CMake as its build system, with Ninja as the preferred generator for efficiency and speed. Follow these steps to build the project:

### 1. Clone the Repository

This repository includes `vcpkg` as a submodule:

```bash
git clone --recurse-submodules https://github.com/yourusername/cpp-template.git
```

If you've already cloned the repository without submodules, run:

```bash
git clone https://github.com/yourusername/cpp-template.git
git submodule update --init --recursive
```

### 2. Bootstrap vcpkg

```bash
cd cpp-template/vcpkg
# Windows:
.\bootstrap-vcpkg.bat
# Linux/macOS:
./bootstrap-vcpkg.sh
```

### 3. Configure the Build

```bash
cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DENABLE_COVERAGE=ON \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_BUILD_TYPE=Debug \
  -G Ninja
```

### 4. Compile the Project

```bash
cd build
ninja
```

### 5. Running Tests Locally

This project uses `gtest_discover_tests` from CMake's GoogleTest module for automatic test discovery.

```bash
cd build
ctest --output-on-failure
```

### 6. Generating Documentation

Generate HTML documentation from code comments using Doxygen:

```bash
# From project root
./scripts/generate_docs.sh
```

The documentation will be available at `build/docs/html/index.html`.

### 7. Generating Coverage Reports

Generate unified HTML coverage reports:

```bash
# From project root, run from build directory
cd build
../scripts/generate_coverage.sh
```

The coverage report will be available at `build/coverage_html/index.html`.

## Utility Scripts

The `scripts/` directory contains helpful utilities:

* **`generate_docs.sh`**: Generates Doxygen documentation
* **`generate_coverage.sh`**: Creates unified coverage reports from test runs
* **`format-code.cmd`**: Windows batch script for code formatting

## Continuous Integration (CI) Pipeline

This repository includes a CircleCI pipeline to ensure high code quality and maintainability. The pipeline performs the following tasks:

### CI Features

* **Dependency Management:** Uses `vcpkg` for package management.
* **Build & Compilation:** Uses `clang` and `Ninja` for efficient builds.
* **Unit Testing**: Runs tests via `ctest` using `Google Test`.
* **Static Analysis:** Utilizes `clang-tidy` for code quality checks.
* **Code Coverage:** Uses `llvm-cov` for coverage reports.
* **Documentation Generation:** Automatically generates and stores HTML documentation using Doxygen.

## Code Formatting

Maintaining code consistency is crucial to this project. We enforce strict formatting guidelines using `clang-format`.

### Apply Formatting

* **Windows:**
```cmd
.\scripts\format-code.cmd
```
* **Linux/macOS:**
```bash
find ./src -iname '*.h' -o -iname '*.cpp' -exec clang-format -i {} +
```

### Check Formatting Without Applying Changes

```bash
find ./src -iname '*.h' -o -iname '*.cpp' -exec clang-format -n -Werror {} +
```

## Running Static Analysis with Clang-Tidy

```bash
clang-tidy ./src/*.cpp -- -I./include
```

## Documentation

This project uses Doxygen to generate comprehensive documentation from source code comments. The documentation includes:

* API documentation for all classes and functions
* Module organization and relationships
* Code examples and usage guidelines
* Automatically generated dependency graphs

To view the documentation, generate it using the script above and open `build/docs/html/index.html` in your web browser.

## License

This project is licensed under the MIT License - see the LICENSE file for details.