
add_executable(no2grm WIN32 main.cpp
        grid.cpp render.cpp)

target_include_directories(no2grm PUBLIC include)
target_link_libraries(no2grm PRIVATE SDL3::SDL3)