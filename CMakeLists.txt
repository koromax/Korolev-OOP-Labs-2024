cmake_minimum_required(VERSION 3.23)

set(project "OOP-Labs-2024")
project("OOP-Labs-2024")

set(CMAKE_CXX_STANDARD 17)

# Set the output directories for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add subprojects
add_subdirectory(lab1)
add_subdirectory(lab2)
# add_subdirectory(lab3)
# add_subdirectory(lab4)
# add_subdirectory(lab5)
# add_subdirectory(lab6)
# add_subdirectory(lab7)
# add_subdirectory(lab8)
