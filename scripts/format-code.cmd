@echo off
REM Format all C++ source files using clang-format

echo Formatting C++ source files...

REM Format headers and source files in src directory
for /r src %%f in (*.h *.hpp *.cpp) do (
    echo Formatting: %%f
    clang-format -i "%%f"
)

REM Format main.cpp
if exist main.cpp (
    echo Formatting: main.cpp
    clang-format -i main.cpp
)

REM Format test files
for /r tests %%f in (*.h *.hpp *.cpp) do (
    echo Formatting: %%f
    clang-format -i "%%f"
)

echo Code formatting complete!
pause