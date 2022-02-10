cmake_minimum_required(VERSION 3.10)

project(shiny-spoon VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "source/*.cpp")
 
add_executable(shiny-spoon ${SOURCES})