cmake_minimum_required(VERSION 3.5)
project(VenomEngine VERSION 0.1 LANGUAGES CXX)

# Setting modules path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/ext/modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/ext/magnum-integration/modules" ${CMAKE_MODULE_PATH})

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)
set(WITH_QT ON CACHE BOOL "" FORCE)
set(WITH_GLXCONTEXT ON CACHE BOOL "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(ext/corrade)
add_subdirectory(ext/magnum)

find_package(OpenGL)
find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED
    GL
    MeshTools
    Primitives
    SceneGraph
    Shaders
)

if(MAGNUM_TARGET_GLES AND NOT MAGNUM_TARGET_DESKTOP_GLES)
    find_package(Magnum REQUIRED EglContext)
elseif(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WglContext)
elseif(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED CglContext)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED GlxContext)
else()
    message(FATAL_ERROR "Magnum context creation is not supported on this platform")
endif()

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
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Magnum::GLContext
    ${OPENGL_LIBRARIES}
    Magnum::GL
    Magnum::Magnum
    Qt${QT_VERSION_MAJOR}::Widgets
    Corrade::Main
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Shaders
    )

# Copying streaming assets
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/stylesheet.qss
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)