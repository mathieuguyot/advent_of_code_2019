cmake_minimum_required(VERSION 2.8.12)
project(MD5Encrypter)

add_definitions("-std=c++14")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES_FILES_LIB
    src/aoc_1.cpp
)

set(HEADERS_FILES
    include/aoc_1.hpp
    include/utils.hpp
)

set(SRC_TEST
    test/aoc_1_test.cpp
    test/aoc_test_main.cpp
)

add_library(aoc_2019_lib ${SOURCES_FILES_LIB} ${HEADERS_FILES})
add_executable(aoc_2019_test ${SRC_TEST})

include_directories(include/ ${CONAN_INCLUDE_DIRS_CATCH2})

target_link_libraries(aoc_2019_test aoc_2019_lib ${CONAN_LIBS})
