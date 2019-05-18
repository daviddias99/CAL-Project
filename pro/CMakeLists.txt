cmake_minimum_required(VERSION 3.13)
project(pro)

set(CMAKE_CXX_STANDARD 14)

add_executable(pro main.cpp Person.h util.cpp util.h Exceptions.cpp Exceptions.h NodeInfo.cpp NodeInfo.h Person.cpp)