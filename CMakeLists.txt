cmake_minimum_required(VERSION 2.8)

project(gravity)

#SET( CMAKE_CXX_FLAGS "-pg" )
SET( CMAKE_CXX_FLAGS "-g" )

find_package(VTK)
include_directories(".")
include(${VTK_USE_FILE})

add_executable(gravity
    Euler.cpp
    Leapfrog.cpp
    main.cpp
    Parser.cpp
    Particule.cpp
    RealTimePlayer.cpp
    Universe.cpp
    Simulator.cpp
    Octree.cpp
    BarnesHut.cpp)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}" )

target_link_libraries(gravity
    ${VTK_LIBRARIES})
