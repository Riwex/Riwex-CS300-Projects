cmake_minimum_required(VERSION 3.30)
project(CS300HW1)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS300HW1 main.cpp
        MenuList.cpp
        OrderQueue.cpp
        PreparedStack.cpp)
