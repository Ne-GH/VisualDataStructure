cmake_minimum_required(VERSION 3.26)
project(VisualDataStructure)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(VisualDataStructure main.cpp
        MainWindow.cpp MainWindow.h
        Logs/Log.h Logs/Log.cpp Logs/Log.ui

        CustomGraphics/CustomGraphics.cpp CustomGraphics/CustomGraphics.h)
target_link_libraries(VisualDataStructure
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
