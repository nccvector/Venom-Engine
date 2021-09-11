cmake_minimum_required(VERSION 3.5)

project(VenomEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Finding Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Setting project sources
set(APP "VenomEngine")
 
set(HDRS
	src/QTOgreWindow.h
	src/SdkQtCameraMan.h
)
 
set(SRCS
	src/QTOgreWindow.cpp
    src/main.cpp
    src/UI/MainWindow.cpp
    ext/BreezeThemes/breeze.qrc
)

# Setting include directories
include_directories(
    src
    src/UI
    src/Shaders
    ext/eigen
)

# Ogre libraries linking
include("tools/cmake/common.cmake")

# Copying streaming assets
file(GLOB StyleSheets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.qss)
foreach(file ${StyleSheets})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/dist/bin COPYONLY)
endforeach()

# Copying streaming assets
file(GLOB Configs ${CMAKE_CURRENT_SOURCE_DIR}/*.cfg)
foreach(file ${Configs})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/dist/bin COPYONLY)
endforeach()