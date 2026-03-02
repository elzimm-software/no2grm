cmake_minimum_required(VERSION 3.26)
project(no2grm CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(NO2GRM_USE_VENDORED "Use vendored libraries" OFF)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not permitted")
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})
if(ipo_supported)
    message("IPO enabled")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

if(NO2GRM_USE_VENDORED)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL Vendored/SDL)
else ()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif ()

add_subdirectory(src Source)
