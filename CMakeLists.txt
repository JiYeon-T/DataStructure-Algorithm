cmake_minimum_required(VERSION 3.5.1)
project(data_structure_algorithm VERSION 0.1)


message("")
message(STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})
message("")

# 加载构建配置文件, 在 ${PROJECT_BINARY_DIR} 目录生成配置文件
configure_file(build_config.h.in build_config.h)

# 设置编译选项
# set_build_option()
set(CMAKE_C_FLAGS -g)
message("CMAKE_C_FLAGS:" ${CMAKE_C_FLAGS})
# set(CMAKE_CXX_FLAGS -g)
# message("CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})

# 收集源文件
file(GLOB SRC_LIST 
    # ${PROJECT_SOURCE_DIR}/data_structure/1_ADT/*.c
    ${PROJECT_SOURCE_DIR}/data_structure/2_linklist/*.c
    # ${PROJECT_SOURCE_DIR}/data_structure/3_ring_buffer/*.c
    # ${PROJECT_SOURCE_DIR}/data_structure/4_list/*.c
    ${PROJECT_SOURCE_DIR}/data_structure/5_polynomail/*.c
    # ${PROJECT_SOURCE_DIR}/data_structure/5_stack_queue/*.c
) 
message("SRC_LIST:" ${SRC_LIST})

# 添加头文件路径
include_directories(
    # ${PROJECT_SOURCE_DIR}/data_structure/1_ADT
    ${PROJECT_SOURCE_DIR}/data_structure/2_linklist
    # ${PROJECT_SOURCE_DIR}/data_structure/3_ring_buffer
    # ${PROJECT_SOURCE_DIR}/data_structure/4_list
    # ${PROJECT_SOURCE_DIR}/data_structure/5_polynomail
    # ${PROJECT_SOURCE_DIR}/data_structure/5_stack_queue
)


# 生成可执行文件
add_executable(
    ${PROJECT_NAME}_test
    main.c
    ${SRC_LIST}
)

# 配置文件头文件目录添加
target_include_directories(
    ${PROJECT_NAME}_test
    PUBLIC
    ${PROJECT_BINARY_DIR}
)