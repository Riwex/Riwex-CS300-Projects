cmake_minimum_required(VERSION 3.26)
project(CS300HW2)
set(CMAKE_CXX_STANDARD 17)

add_executable(CS300HW2
        main.cpp
        OrderTree.cpp
        OrderTree.h
)

target_compile_definitions(CS300HW2 PRIVATE BUILD_STANDALONE)

