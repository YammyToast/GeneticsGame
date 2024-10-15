cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


project(GeneticsGame)

include_directories(/include)

add_executable(GeneticsGame src/main.cpp)