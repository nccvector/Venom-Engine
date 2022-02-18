cmake_minimum_required (VERSION 2.8)
project(MyGuiSample)

# required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 11)

## [discover_ogre]
# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

include_directories(
    ${CMAKE_SOURCE_DIR}/UI
    ${CMAKE_SOURCE_DIR}/UI/imgui
    ${CMAKE_SOURCE_DIR}/States
)

# Adding my gui sample exe
add_executable(${PROJECT_NAME} MyGuiSample.cpp)
target_link_libraries(${PROJECT_NAME} OgreBites)