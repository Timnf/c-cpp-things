cmake_minimum_required(VERSION 3.0.0)
# project(cBase VERSION 0.1.0 LANGUAGES C)
project(loadLibrary VERSION 0.1.0)

add_library(add SHARED library.c)

add_executable(loadLibrary loadLibrary.cpp)
target_link_libraries(loadLibrary add)



  


