cmake_minimum_required(VERSION 3.0)
project(StudyLibrary)

set(CMAKE_CXX_STANDARD 11)

#搜索头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

#设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#搜索源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_subdirectory(src)

add_executable(StudyLibrary main.cpp ${SRC_LIST})

