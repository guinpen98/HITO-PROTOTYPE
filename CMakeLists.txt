cmake_minimum_required(VERSION 3.16)
project(HITO)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH bin)

add_subdirectory(Library/NLP/src)

include_directories(Library/NLP/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(CUIHITO CharacterUserInterface/Main.cpp CharacterUserInterface/dialogue_scene.hpp)
target_link_libraries(CUIHITO mecab hito)