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

find_package(Lua51)
include_directories(${LUA_INCLUDE_DIR})


INCLUDE_DIRECTORIES(Graphics VisualStructure MSTL Setting)

add_executable(VisualDataStructure main.cpp
        MainWindow.cpp MainWindow.h

        Graphics/GraphicsView.h
        Graphics/GraphicsScene.h
        Graphics/GraphicsItem.h
        Graphics/ArrowItem.h

        VisualStructure/VisualStructureBase.hpp
        VisualStructure/VisualArray.hpp
        VisualStructure/VisualSort.h
        VisualStructure/VisualList.hpp

        MSTL/Array.hpp
        MSTL/BinaryTree.hpp
        MSTL/Find.hpp
        MSTL/List.hpp
        MSTL/Map.hpp
        MSTL/Queue.hpp
        MSTL/Stack.hpp
        MSTL/Sort.hpp

        Setting/Setting.h
        Setting/Setting.cpp

        )

target_link_libraries(VisualDataStructure
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        )

set(VERSION "0.1")
add_compile_definitions(VERSION="${VERSION}")

#set(CMAKE_BUILD_TYPE "Release")

