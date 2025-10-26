add_library(first_task FirstTask.cpp)
target_link_libraries(first_task PUBLIC emulator)
target_include_directories(first_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
