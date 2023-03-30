cmake_minimum_required(VERSION 3.16)
project(HITO)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ../bin)

include_directories(../include)
add_library(libhito SHARED Library/dialogue_scene.hpp)
target_link_libraries(libhito ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libmecab.lib)

include_directories(Library)
add_executable(CUIHITO Main.cpp)
target_link_libraries(CUIHITO libhito)