cmake_minimum_required(VERSION 2.8)

project(projetAstro)

find_package(VTK)
include_directories(".")
include(${VTK_USE_FILE})

add_executable(projetAstro
    Euler.cpp
    Leapfrog.cpp
    main.cpp
    Parser.cpp
    Particule.cpp
    RealTimePlayer.cpp
    Universe.cpp
    Initialize.cpp
    Simulator.cpp)

target_link_libraries(projetAstro
    ${VTK_LIBRARIES})
