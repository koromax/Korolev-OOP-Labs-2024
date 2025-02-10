cmake_minimum_required(VERSION 3.23)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp)

IF (NOT WIN32)
target_link_libraries(lab1 m)
ENDIF()
