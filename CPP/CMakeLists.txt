cmake_minimum_required(VERSION 3.0.0)

# project(CPPLearn LANGUAGE CPP)

set(target NFCPPLearn)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

file(GLOB source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


foreach(SRC ${source})
get_filename_component(EXE ${SRC} NAME_WE)
add_executable(${EXE} ${SRC})
endforeach()

add_subdirectory(cppthings)