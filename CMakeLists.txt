cmake_minimum_required(VERSION 3.29)
project(c__chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(c__chess
    Board.cpp
    Main.cpp
        Pawn.cpp)
