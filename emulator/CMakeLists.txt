cmake_minimum_required(VERSION 4.0)
project(emulator)

set(CMAKE_CXX_STANDARD 20)

add_library(emulator STATIC Emulator.cpp
)
