cmake_minimum_required(VERSION 3.22)
project(lc_cpp)

# 输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

# C 和 C++ 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# WSL 环境
message(STATUS "Configuring for WSL environment")
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE FILEPATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE FILEPATH "C++ compiler" FORCE)

# 默认编译类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type" FORCE)
endif()
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

# 编译选项
add_compile_options(-Wall -Wextra -fno-omit-frame-pointer)

# LLD 链接器
find_program(LLD_LINKER ld.lld)
if(LLD_LINKER)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld")
    message(STATUS "Using LLD linker: ${LLD_LINKER}")
else()
    message(WARNING "LLD linker not found, using default linker")
endif()

# 这里手动改成你要编译的题目文件（相对路径即可）
set(SOURCE_FILE lcCpp/dp/lc_1178NumberofValidWordsforEachPuzzle.cpp)

# 检查文件是否存在
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE}")
    message(FATAL_ERROR "Source file not found: ${SOURCE_FILE}")
endif()

# 取文件名作为可执行文件名
get_filename_component(EXECUTABLE_NAME "${SOURCE_FILE}" NAME_WE)

# 生成可执行文件
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})

# 编译特性和优化
target_compile_features(${EXECUTABLE_NAME} PRIVATE c_std_11)
target_compile_options(${EXECUTABLE_NAME} PRIVATE
        -Wall -Wextra
        "$<$<CONFIG:Debug>:-O0;-g3;-gdwarf-4>"
        "$<$<CONFIG:Release>:-O3;-flto>"
        -fno-omit-frame-pointer
)

# UTF-8 编码
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

# Ninja 并行编译
if(CMAKE_GENERATOR STREQUAL "Ninja")
    if(NOT DEFINED CMAKE_BUILD_PARALLEL_LEVEL)
        include(ProcessorCount)
        ProcessorCount(N)
        if(NOT N EQUAL 0)
            set(CMAKE_BUILD_PARALLEL_LEVEL ${N} CACHE STRING "Number of parallel build jobs")
            message(STATUS "Setting parallel build jobs to: ${N}")
        endif()
    endif()
endif()
