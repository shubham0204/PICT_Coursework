cmake_minimum_required(VERSION 3.1...3.27)

project(
    schedulers 
    LANGUAGES CXX
)

set(
    SOURCES 
    src/main.cpp src/process.hpp src/first_come_first_serve.cpp src/priority.cpp src/shortest_job_first.cpp src/round_robin.cpp
)

add_executable( schedulers ${SOURCES} )