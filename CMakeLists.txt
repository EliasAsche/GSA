cmake_minimum_required(VERSION 3.26)
project(GSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(GSA main.cpp
        Transactions.cpp
        Transactions.h
        Transactions.cpp)
