cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    GeneticsGame
    VERSION 0.0.1
    DESCRIPTION "GeneticsGame..."
    LANGUAGES CXX
)


add_subdirectory(include)
add_subdirectory(src)

# include(GTest)
# add_executable(GeneticsGame src/main.cpp)