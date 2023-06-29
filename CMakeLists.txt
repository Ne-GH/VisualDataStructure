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
        Charts
        REQUIRED)

INCLUDE_DIRECTORIES(Graphics VisualStructure Logs MSTL)
add_executable(VisualDataStructure main.cpp
        MainWindow.cpp MainWindow.h
        Logs/Log.h Logs/Log.cpp Logs/Log.ui

        Graphics/GraphicsView.h
        Graphics/GraphicsScene.h
        Graphics/GraphicsItem.h

        VisualStructure/VisualStructureBase.hpp
        VisualStructure/VisualArray.hpp
        VisualStructure/VisualSort.h

        MSTL/MArray.hpp

        )

target_link_libraries(VisualDataStructure
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        )
