cmake_minimum_required(VERSION 3.14)

project(kdiff VERSION 1.0 LANGUAGES CXX)

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
    ${SOURCE_DIR}/kdiff/differ/line/LineDifferDecorator.cpp
    ${SOURCE_DIR}/kdiff/differ/line/RangeDecorator.cpp
    ${SOURCE_DIR}/kdiff/differ/line/RangeException.cpp
    ${SOURCE_DIR}/kdiff/differ/line/CaseSensitiveDecorator.cpp
    ${SOURCE_DIR}/kdiff/differ/line/IgnoringSymbolDecorator.cpp
    ${SOURCE_DIR}/kdiff/differ/LineDifferFactory.cpp
)

add_executable(kdiff ${DIFF_SOURCES})

target_include_directories(kdiff PRIVATE ${INCLUDE_DIR})