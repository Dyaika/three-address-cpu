cmake_minimum_required(VERSION 4.0)
project(emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(app
        Emulator/Emulator.cpp
        FirstTask/FirstTask.cpp
        ConsoleApp.cpp
        Emulator/Commands.h
)

add_library(emulator
        Emulator/Emulator.cpp
        Emulator/Commands.h
)
