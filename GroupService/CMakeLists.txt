cmake_minimum_required(VERSION 3.0)
# 定义工程名
project(GroupService)


# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g) # 输出可调试的可执行文件

# 配置最终可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置项目库文件的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 配置项目库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 配置头文件的搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/mprpc)
include_directories(${PROJECT_SOURCE_DIR}/include/proto)
include_directories(${PROJECT_SOURCE_DIR}/include/model)
include_directories(${PROJECT_SOURCE_DIR}/include/connectionpool)
include_directories(${PROJECT_SOURCE_DIR}/include/redis)
include_directories(${PROJECT_SOURCE_DIR}/include/reactorX)


# 设置项目库文件的搜索路径 -L
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# 加载子目录
add_subdirectory(src)
add_subdirectory(example)