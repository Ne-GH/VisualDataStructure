cmake_minimum_required(VERSION 3.26)
project(VisualDataStructure CXX)


set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)

# Skip this line if you're using Clang (>= 16)
#include(cxx_modules_rules_clang.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_library(Hello)



find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)



INCLUDE_DIRECTORIES(Graphics VisualStructure MSTL Setting AboutDialog)


add_library(VisualModules)
target_sources(VisualModules
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        MSTL/Array.cppm
        MSTL/Stack.cppm
        MSTL/Sort.cppm
        MSTL/Queue.cppm
        MSTL/Find.cppm
        MSTL/List.cppm
)


add_executable(VisualDataStructure main.cpp
        MainWindow.cpp MainWindow.h

        Graphics/GraphicsView.h
        Graphics/GraphicsScene.h
        Graphics/GraphicsItem.h
        Graphics/ArrowItem.h

        VisualStructure/VisualStructureBase.hpp
        VisualStructure/VisualArray.hpp
        VisualStructure/VisualStack.hpp
        VisualStructure/VisualQueue.hpp
        VisualStructure/VisualList.hpp
        VisualStructure/VisualTree.hpp
        VisualStructure/VisualSort.h

        MSTL/Map.hpp
        MSTL/BinaryTree.hpp

        Setting/Setting.h
        Setting/Setting.cpp

        AboutDialog/AboutDialog.cpp
        AboutDialog/AboutDialog.h
        AboutDialog/AboutDialog.ui
        Resource.qrc
)
#target_link_libraries(VisualStructure Hello stdc++)
target_link_libraries(VisualDataStructure
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        VisualModules
        )

set(VERSION "1.0")
add_compile_definitions(VERSION="${VERSION}")

#set(CMAKE_BUILD_TYPE "Release")
