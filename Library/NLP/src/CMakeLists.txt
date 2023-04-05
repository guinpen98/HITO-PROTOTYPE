# ヘッダーファイルの場所を指定
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../lib)

set(LIBRARY_OUTPUT_PATH ../../../../lib)

# ソースコードを追加
add_library(hito
            STATIC
            analyzer.cpp
            data.cpp
            dialogue_manager.cpp
            morpheme.cpp
            nlu.cpp
            sentence.cpp
            )

# リンクするライブラリを指定
# target_link_libraries(hito mecab)