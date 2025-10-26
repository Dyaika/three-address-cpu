set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2 COMPONENTS Widgets REQUIRED)

add_executable(gui_app
        GuiApp.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

target_link_libraries(gui_app PRIVATE Qt6::Widgets emulator)
