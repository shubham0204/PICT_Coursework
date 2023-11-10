cmake_minimum_required(VERSION 3.1...3.27)

project(
    schedulers 
    LANGUAGES CXX
)

set(
    SOURCES 
    src/main.cpp
)

add_executable( assembler ${SOURCES} )