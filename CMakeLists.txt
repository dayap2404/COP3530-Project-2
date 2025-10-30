cmake_minimum_required(VERSION 3.10)
project(MovieRanks)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(MovieRanks
        src/main.cpp
        src/movie.cpp
        src/merge_sort.cpp
        src/heap_sort.cpp
)
