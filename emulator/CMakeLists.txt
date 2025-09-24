cmake_minimum_required(VERSION 4.0)
project(emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(app
        FirstTask/Emulator.cpp
        FirstTask/ConsoleApp.cpp
)

add_library(emulator
        FirstTask/Emulator.cpp
        FirstTask/ConsoleApp.cpp
)
