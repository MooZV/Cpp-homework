cmake_minimum_required(VERSION 3.2)
project(project3)

set(CMAKE_CXX_STANDARD  14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(${PROJECT_NAME} main.cpp conversion.cpp)

