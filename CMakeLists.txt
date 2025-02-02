cmake_minimum_required(VERSION 3.27)

# 设置项目信息
set(PROJECT_NAME BlackHoleSim)

# 导出 CompileCommands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置编译器，可自行修改成 GCC
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置优化选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

project(${PROJECT_NAME})

# 添加 Eigen 库
find_package(Eigen3 REQUIRED)
if(Eigen3_FOUND)
    include_directories(${Eigen3_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Eigen3 not found")
endif()

# 添加源文件
set(SOURCE
    src/main.cpp
    src/gr.cpp
    src/ppm.cpp
)

# 添加头文件
include_directories(include)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${Eigen3_LIBRARIES})
