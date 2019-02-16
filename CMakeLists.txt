cmake_minimum_required(VERSION 3.2)

project(RayTracingDemos)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -fopenmp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(.)

add_executable(alpaca
        main.cpp
        stdafx.h impl/objects.h impl/objects.cpp impl/materials.h impl/materials.cpp
        core/math.h core/math.cpp
        core/engine.h core/engin.cpp core/camera.h core/camera.cpp core/graph.h core/graph.cpp core/common.h)
