cmake_minimum_required(VERSION 2.8)

set(PACKAGE_NAME JResult)
set(PACKAGE_VERSION 1.0.0)

project(${PACKAGE_NAME})
message(STATUS "Building ${PACKAGE_NAME} ${PACKAGE_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Enable code coverage
option(ENABLE_COVERAGE "Use GCOV" OFF)
message(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
endif()

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    enable_testing()
    add_subdirectory(ut)
endif()