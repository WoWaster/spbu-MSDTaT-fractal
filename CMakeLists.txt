cmake_minimum_required(VERSION 3.10)

project(FractalGenerator C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Compile flags
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
add_compile_options(-Wall -Wextra -Wpedantic)

# Define source files - now multiple files
set(SOURCES
    src/main.c
    src/image.c
    src/fractal.c
    src/cli.c
)

add_executable(fractal_gen ${SOURCES})

target_link_libraries(fractal_gen m)
