cmake_minimum_required(VERSION 3.25)
project(Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project main.cpp
        cpp/Case.cpp
        headers/Case.h
        cpp/Game.cpp
        headers/Game.h
        cpp/Player.cpp
        headers/Player.h
        cpp/Tile.cpp
        headers/Tile.h)
target_link_libraries(Project winmm.lib)

