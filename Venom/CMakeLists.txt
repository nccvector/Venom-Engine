cmake_minimum_required(VERSION 3.10)

project(Venom VERSION 0.1)

# Making Venom-Engine as a library
add_library(${PROJECT_NAME} SHARED
    src/Venom/Core/Application.cpp
    src/Venom/Core/Log.cpp
)

# include directory for Engine
target_include_directories(${PROJECT_NAME} PUBLIC ./src)

# Linking spdlog with Venom-Engine lib
set(SPDLOG_BUILD_SHARED ON CACHE BOOL "Build shared library" FORCE) # Setting the build flag
add_subdirectory(ext/spdlog)                                        # Adding subdirectory
target_include_directories(${PROJECT_NAME} PUBLIC ./ext)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)       # Linking dynamic library