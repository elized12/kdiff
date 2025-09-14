cmake_minimum_required(VERSION 3.14)

project(file-diff V1.0)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

set(DIFF_SOURCES
    main.cpp
)

add_executable(file-diff ${DIFF_SOURCES})

target_include_directories(file-diff ${INCLUDE_DIR})