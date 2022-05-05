cmake_minimum_required(VERSION 3.0)

project(raylibproj)

# Adding raylib as a library
add_subdirectory(ext/raylib)

# Adding imgui sources
file(GLOB ImGuiSources ext/imgui/*.cpp)

# Adding all includes
include_directories(
    src
    src/widgets
    src/widgets/viewports
    ext
    ext/imgui 
    ext/imgui/backends
    ext/raylib/src/external 
    ext/raylib/src
)

# Source
file(GLOB SRCS src/*.cpp)

add_executable(${PROJECT_NAME}
    main.cpp
    ${SRCS}
    ext/rlImGui.cpp
    ${ImGuiSources}
)

# Linking to libs
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

# Copying resources
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})