cmake_minimum_required(VERSION 3.0.0)

project(hello_cmake)

message("hello cmake test")
message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
message("CMAKE_CURRENT_BINARY_DIR:${CMAKE_CURRENT_BINARY_DIR}")
message("PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")

add_executable(hello_cmake hellow.c)

target_include_directories(hello_cmake PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/inlcude)