cmake_minimum_required(VERSION 3.16)
project(HITO)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_OSX_ARCHITECTURES x86_64)
set(EXECUTABLE_OUTPUT_PATH bin)

add_subdirectory(Library/NLP/src)

include_directories(Library/NLP/include)
link_directories(bin)

add_executable(CUIHITO CharacterUserInterface/Main.cpp CharacterUserInterface/dialogue_scene.hpp)
target_link_libraries(CUIHITO mecab hito)