cmake_minimum_required(VERSION 3.0)

project(raylibproj)

# Adding raylib as a library
add_subdirectory(ext/raylib)

# Adding imgui sources
file(GLOB ImGuiSources ext/imgui/*.cpp)

# Adding all includes
include_directories(
    ext
    ext/imgui 
    ext/imgui/backends
    ext/raylib/src/external 
    ext/raylib/src
)

add_executable(${PROJECT_NAME}
    main.cpp
    ext/rlImGui.cpp
    ${ImGuiSources}
)

# Linking to libs
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

# Copying resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})