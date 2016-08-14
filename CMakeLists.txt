cmake_minimum_required (VERSION 3.1.0)
project (Game2048)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14 -stdlib=libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lncurses")

include_directories("${CMAKE_SOURCE_DIR}")

add_executable (game console/main.cpp console/console2048.cpp core/board.cpp core/subject.cpp
    core/game.cpp)
