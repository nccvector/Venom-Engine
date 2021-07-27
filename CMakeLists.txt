cmake_minimum_required(VERSION 3.4)
project(VenomEngine)

set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/ext/imgui" ${CMAKE_PREFIX_PATH})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/ext/modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/ext/magnum-integration/modules" ${CMAKE_MODULE_PATH})

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

# SETTING IMGUI OPTION
set(WITH_IMGUI ON CACHE BOOL "" FORCE) # Magnum integration
# set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
set(WITH_GLFWAPPLICATION ON CACHE BOOL "" FORCE)

# Add Corrade as a subproject
add_subdirectory(ext/corrade EXCLUDE_FROM_ALL)
add_subdirectory(ext/magnum EXCLUDE_FROM_ALL)
add_subdirectory(ext/magnum-integration EXCLUDE_FROM_ALL)

## Adding ImGuizmo and include folder
include_directories(${PROJECT_SOURCE_DIR}/ext/ImGuizmo)
include_directories(${PROJECT_SOURCE_DIR}/include)

# FINDING AND LINKING
find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED
    GL
    GlfwApplication
    MeshTools
    Primitives
    SceneGraph
    Shaders
)
find_package(MagnumIntegration REQUIRED ImGui)

# Getting files from include
file(GLOB_RECURSE SRC_H_FILES ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SRC_CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# CREATING EXECUTABLE
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/ext/ImGuizmo/ImGuizmo.cpp
    ${INCLUDE_H_FILES}
    ${SRC_H_FILES}
    ${INCLUDE_CPP_FILES}
    ${SRC_CPP_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Shaders
    MagnumIntegration::ImGui
)

# add_subdirectory(src)