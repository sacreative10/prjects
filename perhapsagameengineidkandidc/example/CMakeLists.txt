cmake_minimum_required(VERSION 3.0.0)
project(example VERSION 0.1.0)
# link to gameengineidk library 
set(CMAKE_CXX_STANDARD 20)
# add external library which is a folder above


add_executable(example main.cpp)
target_link_libraries(example gameengineidk)

