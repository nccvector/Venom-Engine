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
set(PROJECT_SOURCES
        src/main.cpp
        src/UI/MainWindow.cpp
        src/MyOpenGLWidget.cpp
        ext/BreezeThemes/breeze.qrc
)

# Setting include directories
include_directories(
    src
    src/UI
    src/Shaders
    /usr/include/panda3d
    ext/eigen
)

# Panda libraries path
link_directories(/usr/lib/x86_64-linux-gnu/panda3d)

# Setting up themes
# include(ext/modules/BreezeThemes.cmake)

# Adding executable
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# Linking qt with executable
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    p3framework
    panda
    pandafx
    pandaexpress
    p3dtoolconfig
    p3dtool
    p3direct
    pthread
)

# Copying streaming assets
file(GLOB StyleSheets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.qss)
foreach(file ${StyleSheets})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()