cmake_minimum_required(VERSION 4.0)
project(Lab2_Notebook)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab2_Notebook main.cpp
        Note.cpp
        Note.h
        Keeper.h
        Keeper.cpp
        task2.cpp
        task2.h)
