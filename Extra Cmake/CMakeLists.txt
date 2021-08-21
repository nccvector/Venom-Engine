cmake_minimum_required(VERSION 3.5)

project(MyApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(OpenGL REQUIRED COMPONENTS OpenGL)
# find_package(GLUT REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets OpenGL REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        MyOpenGLWidget.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MyApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(MyApp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MyApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(MyApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL)
# target_link_libraries(MyApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Copying streaming assets
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/stylesheet.qss
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set_target_properties(MyApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyApp)
endif()
