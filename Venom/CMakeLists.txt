cmake_minimum_required(VERSION 3.10)

project(Venom VERSION 0.1)

add_library(${PROJECT_NAME} SHARED 
    src/Venom.h 
    src/Venom/Core/Core.h
    src/Venom/Core/Application.h
    src/Venom/Core/Application.cpp
    src/Venom/Core/EntryPoint.h
)