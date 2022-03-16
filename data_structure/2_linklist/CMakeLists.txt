cmake_minimum_required(VERSION 2.8)
project(LinkList)


# 添加包含路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/linklist_test
)

aux_source_directory(linklist_test SRC_LIST)
message("file:" ${SRC_LIST})

# 编译外部源文件
add_library(LL STATIC ${SRC_LIST}) # 静态库

# 编译 项目源文件
add_executable(${PROJECT_NAME} main.c)

# 生成目标文件
target_link_libraries(${PROJECT_NAME} LL)

# cmake -G "Unix Makefiles" ../