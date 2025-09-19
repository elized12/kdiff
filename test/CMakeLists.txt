find_package(GTest REQUIRED)

set(TEST_SOURCES
    ParserTest.cpp
    MayerTest.cpp
)

add_executable(kdiff_tests ${TEST_SOURCES})

target_link_libraries(kdiff_tests PRIVATE
    GTest::gtest_main
    GTest::gmock
    kdiff_lib
)

target_include_directories(kdiff_tests PRIVATE 
${CMAKE_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(GoogleTest)

gtest_discover_tests(kdiff_tests)
