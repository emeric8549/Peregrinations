cmake_minimum_required(VERSION 3.16)
project(TSPGNN LANGUAGES CXX CUDA)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Release build if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add src and include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Torch dependencies (assuming LibTorch is installed)
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libtorch")
find_package(Torch REQUIRED)

# Main executable
add_executable(tsp_gen
    src/main.cpp
    src/distances.cpp
    src/data/data_generator.cpp
    src/nearest_neighbor.cpp
    src/two_opt.cpp
)

# Link Torch
target_link_libraries(tsp_gen "${TORCH_LIBRARIES}")
set_property(TARGET tsp_gen PROPERTY CXX_STANDARD 17)