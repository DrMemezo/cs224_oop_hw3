cmake_minimum_required(VERSION 3.16)

project(OOP_HW3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_sources(${PROJECT_NAME} PRIVATE 
    src/Canvas.cpp
    src/Grid.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE include
)
