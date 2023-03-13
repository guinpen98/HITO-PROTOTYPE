cmake_minimum_required(VERSION 3.16)
project(HITO)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ../CharacterUserInterface/bin)
include_directories(../Library)

add_executable(GeographicDataToSimulationGrid Main.cpp)

