cmake_minimum_required(VERSION 3.23)
project(lab8)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab8 main.cpp)

IF (NOT WIN32)
target_link_libraries(lab8 m)
ENDIF()
