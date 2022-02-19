cmake_minimum_required (VERSION 3.0)
project(VenomEngine)

# required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 17)

## [discover_ogre]
# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

include_directories(
    ${CMAKE_SOURCE_DIR}/UI
    ${CMAKE_SOURCE_DIR}/UI/imgui
    ${CMAKE_SOURCE_DIR}/States
    ${CMAKE_SOURCE_DIR}/States/Abstract
    ${CMAKE_SOURCE_DIR}/Application
)

# Adding my gui sample exe
add_executable(${PROJECT_NAME} 
    VenomEngine.cpp
    Application/Application.cpp
    UI/UIMain.cpp
    States/PickState.cpp
    States/MoveState.cpp
    States/RotateState.cpp
    States/ScaleState.cpp
    )
target_link_libraries(${PROJECT_NAME} OgreBites)