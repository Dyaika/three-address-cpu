add_library(emulator
        Emulator.cpp
        Commands.h
)
target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
