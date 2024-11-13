# JResult: A cpp function return with infomations

## 引用

### CMake

```CMakeList.txt
# 假设将JResult放到third_party目录中：
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/JResult)
add_executable(execute_target ${ALL_SRCS})
target_link_libraries(execute_target JResult)
```