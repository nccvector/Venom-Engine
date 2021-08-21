cmake_minimum_required(VERSION 3.5)

project(VenomEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/UI/MainWindow.cpp
        src/MyOpenGLWidget.cpp
)

# Setting include directories
include_directories(
    src
    src/UI
    src/Shaders
)

# Adding executable
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# Linking qt with executable
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Copying streaming assets
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/stylesheet.qss
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)