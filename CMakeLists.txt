cmake_minimum_required(VERSION 3.0.0)
# project(cBase VERSION 0.1.0 LANGUAGES C)
project(cBase VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_MAKE_PROGRAM on)

add_subdirectory(cmaketest)

add_subdirectory(loadLibrary)

add_subdirectory(C)

add_subdirectory(CPP)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# learn cmake
message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
include(CMake/cmakeUtil.cmake)