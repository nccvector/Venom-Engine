cmake_minimum_required(VERSION 3.10)

project(VenomSandboxApp VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Making MyLib as VenomLib
add_subdirectory(Venom)
add_subdirectory(Sandbox)