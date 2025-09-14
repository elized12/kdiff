cmake_minimum_required(VERSION 3.14)

project(file-diff VERSION 1.0 LANGUAGES CXX)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DIFF_SOURCES
    main.cpp
    ${SOURCE_DIR}/kdiff/Config.cpp
    ${SOURCE_DIR}/kdiff/Difference.cpp
    ${SOURCE_DIR}/kdiff/Parser.cpp
    ${SOURCE_DIR}/kdiff/ParserException.cpp
    ${SOURCE_DIR}/kdiff/differ/LineDiffer.cpp
    ${SOURCE_DIR}/kdiff/algorithm/line/Mayer.cpp
    ${SOURCE_DIR}/kdiff/ui/DiffRender.cpp
    ${SOURCE_DIR}/kdiff/ui/RenderException.cpp
)

add_executable(file-diff ${DIFF_SOURCES})

target_include_directories(file-diff PRIVATE ${INCLUDE_DIR})