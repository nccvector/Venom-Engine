add_executable(${PROJECT_NAME} src/Sandbox.cpp)

# Linking Sandbox app with Venom
target_include_directories(${PROJECT_NAME} PUBLIC ../Venom/src)
target_link_libraries(${PROJECT_NAME} Venom)