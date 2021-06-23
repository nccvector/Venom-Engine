cmake_minimum_required(VERSION 3.10)

project(VenomEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adding glfw
add_subdirectory(ext/glfw)
link_libraries(glfw)

# Adding src
add_subdirectory(src)


# # Linking spdlog with Venom-Engine lib
# set(SPDLOG_BUILD_SHARED ON CACHE BOOL "Build shared library" FORCE) # Setting the build flag
# add_subdirectory(ext/spdlog) 