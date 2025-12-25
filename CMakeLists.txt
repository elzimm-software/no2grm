cmake_minimum_required(VERSION 3.31)
project(nonogram)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/raylib)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp
        src/bounds.cpp
        src/grid.cpp
        src/states/create.cpp
        src/states/home.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)