cmake_minimum_required(VERSION 3.23)

set(project "lab4")

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main.cpp)

add_subdirectory(MyStack)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

if(ENABLE_DEBUG)
    target_compile_options(${project} PRIVATE -g)
endif()

target_link_libraries(${project} MyStack)