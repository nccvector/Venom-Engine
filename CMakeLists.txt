cmake_minimum_required(VERSION 3.10)

project(VenomEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Making Venom-Engine as a library
add_executable(${PROJECT_NAME}
    Venom/Core/EntryPoint.cpp
    Venom/Core/Log.cpp
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

# # Linking spdlog with Venom-Engine lib
# set(SPDLOG_BUILD_SHARED ON CACHE BOOL "Build shared library" FORCE) # Setting the build flag
# add_subdirectory(ext/spdlog) 