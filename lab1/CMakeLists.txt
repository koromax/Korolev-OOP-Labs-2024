cmake_minimum_required(VERSION 3.23)

set(project "lab1")

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main.cpp)

add_subdirectory(newmath)
add_subdirectory(ConsoleController)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} newmath)
target_link_libraries(${project} ConsoleController)