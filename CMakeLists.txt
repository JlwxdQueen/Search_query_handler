cmake_minimum_required(VERSION 3.30)
project(Search_query_handler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Search_query_handler main.cpp
        src/Lot.cpp
        include/Lot.h
        src/Tokenizer.cpp
        include/Tokenizer.h
        include/relevanceProcessor.h
        src/relevanceProcessor.cpp
        tools/setup.h
)
