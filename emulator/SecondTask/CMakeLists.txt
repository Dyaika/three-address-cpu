add_library(second_task SecondTask.cpp)
target_link_libraries(second_task PUBLIC emulator)
target_include_directories(second_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
