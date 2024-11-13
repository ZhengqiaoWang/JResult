cmake_minimum_required(VERSION 3.11)

set(PACKAGE_NAME JResult)
set(PACKAGE_VERSION 1.0.0)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION})
message(STATUS "Building ${PACKAGE_NAME} ${PACKAGE_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# 创建一个接口库
add_library(JResult INTERFACE)

# 设置头文件路径
target_include_directories(JResult INTERFACE ${PROJECT_SOURCE_DIR}/include)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # 设置单元测试
    option(ENABLE_COVERAGE "Use GCOV" OFF)
    message(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
    if(ENABLE_COVERAGE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
    endif()
    enable_testing()
    add_subdirectory(ut)
endif()