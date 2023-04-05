cmake_minimum_required(VERSION 3.20)
project(Task1Assignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(Task1Assignment
        MainRunner.cpp
        InputValidation.cpp
        GameMapManager.cpp
        Cell.cpp
        Village.cpp
        Buildings.cpp
        ResourceGenerator.cpp
        Barracks.cpp
        Troops.cpp
        Army.cpp
        Resources.cpp)
