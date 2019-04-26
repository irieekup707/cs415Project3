cmake_minimum_required(VERSION 3.12)
project(cs415Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs415Project3
    bst.cpp
    bst.h
    main.cpp
    TT.cpp
    TT.h)
