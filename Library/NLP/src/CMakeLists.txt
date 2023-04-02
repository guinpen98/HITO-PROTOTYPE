set(EXECUTABLE_OUTPUT_PATH ../../../bin)
include_directories(../../../include)
add_library(libhito
            SHARED
            analyzer.cpp
            data.cpp
            dialogue_manager.cpp
            morpheme.cpp
            nlu.cpp
            sentence.cpp
            )
target_link_libraries(libhito ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/libmecab.lib)
