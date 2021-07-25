cmake_minimum_required(VERSION 3.10)

project(VenomEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Making Venom-Engine as a library
add_executable(${PROJECT_NAME}
    Venom/EntryPoint.cpp
    Venom/Core/Application.cpp
    Venom/Core/Log.cpp
    Venom/Core/Window.cpp
    Venom/Core/Layer.cpp
    Venom/Core/LayerStack.cpp
    Venom/Gui/ImGuiLayer.cpp
)

# Adding Venom as an include directory
target_include_directories(${PROJECT_NAME} PUBLIC Venom)

# Adding spdlog
set(SPDLOG_BUILD_SHARED ON CACHE BOOL "Build shared library" FORCE) # Setting the build flag
add_subdirectory(ext/spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

# Adding glfw
add_subdirectory(ext/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Adding glfw
add_subdirectory(ext/glad)
target_link_libraries(${PROJECT_NAME} glad)

# Adding imgui as a library
# include_directories(ext/imgui)

add_library(ImGui SHARED
  ext/imgui/imgui.cpp
  ext/imgui/imgui_demo.cpp
  ext/imgui/imgui_draw.cpp
  ext/imgui/imgui_tables.cpp
  ext/imgui/imgui_widgets.cpp
  ext/imgui/backends/imgui_impl_glfw.cpp
  ext/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImGui PUBLIC
  ext/imgui
  ext/imgui/backends
)

# Liking glad with imgui
target_link_libraries(ImGui glad)

# Linking imgui with Venom engine
target_link_libraries(${PROJECT_NAME} ImGui)

# # Linking spdlog with Venom-Engine lib
# set(SPDLOG_BUILD_SHARED ON CACHE BOOL "Build shared library" FORCE) # Setting the build flag
# add_subdirectory(ext/spdlog) 