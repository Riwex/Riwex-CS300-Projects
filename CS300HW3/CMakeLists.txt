cmake_minimum_required(VERSION 3.20)
project(HW3CS300s LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HW3CS300s
        main.cpp
        hash_experiment.cpp
        hash_table.cpp
)
