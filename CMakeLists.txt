cmake_minimum_required(VERSION 3.28)
project(VisualDataStructure)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(/utf-8)
	set(close_console_flag WIN32)
	message("this is windows")
endif ()


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_library(Module)
target_sources(Module
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Config/Config.cppm
)

#find_package(jsoncpp REQUIRED)
#include_directories(${JSONCPP_INCLUDE_DIR})

INCLUDE_DIRECTORIES(Graphics VisualStructure MSTL Setting AboutDialog)

add_executable(VisualDataStructure
	${close_console_flag}

	main.cpp
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

	AboutDialog/AboutDialog.cpp
	AboutDialog/AboutDialog.h
	AboutDialog/AboutDialog.ui

	Config/Interpreter.cpp

	Resource.qrc
	Macros.h
)

target_link_libraries(VisualDataStructure
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        Module
#        jsoncpp
        )

set(VERSION "1.0")
add_compile_definitions(VERSION="${VERSION}")

# set(CMAKE_BUILD_TYPE "Release")

