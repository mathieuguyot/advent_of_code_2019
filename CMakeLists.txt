cmake_minimum_required(VERSION 2.8.12)
project(MD5Encrypter)

add_definitions("-std=c++14")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES_FILES_LIB
    src/aoc_1.cpp
    src/aoc_2.cpp
    src/aoc_3.cpp
    src/aoc_4.cpp
    src/aoc_6.cpp
    src/aoc_7.cpp
    src/intcode_computer.cpp
)

set(HEADERS_FILES
    include/aoc_1.hpp
    include/aoc_2.hpp
    include/aoc_3.hpp
    include/aoc_4.hpp
    include/aoc_6.hpp
    include/aoc_7.hpp
    include/intcode_computer.hpp
    include/utils.hpp
)

set(SRC_TEST
    test/aoc_1_test.cpp
    test/aoc_2_test.cpp
    test/aoc_3_test.cpp
    test/aoc_4_test.cpp
    test/aoc_5_test.cpp
    test/aoc_6_test.cpp
    test/aoc_7_test.cpp
    test/intcode_computer_test.cpp
    test/aoc_test_main.cpp
)

find_package(Threads)

add_library(aoc_2019_lib ${SOURCES_FILES_LIB} ${HEADERS_FILES})
add_executable(aoc_2019_test ${SRC_TEST})

include_directories(include/ ${CONAN_INCLUDE_DIRS_CATCH2})

target_link_libraries(aoc_2019_test aoc_2019_lib ${CONAN_LIBS} ${CMAKE_THREAD_LIBS_INIT})
