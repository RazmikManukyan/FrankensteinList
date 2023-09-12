cmake_minimum_required(VERSION 3.26)
project(Frankenstein_s_list)

set(CMAKE_CXX_STANDARD 17)

add_executable(Frankenstein_s_list main.cpp
        Node.h
        FrankensteinList.h
        FrankensteinList.tpp)
