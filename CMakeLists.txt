cmake_minimum_required(VERSION 3.0)
project(test_01)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(
        /home/dp/miniconda3/envs/torch1.4/include/python3.6m
        /home/dp/miniconda3/envs/torch1.4/lib/python3.6/site-packages/numpy/core/include
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(test_01 main.cpp utils.cpp utils.h)

target_link_libraries(test_01
        /home/dp/miniconda3/envs/torch1.4/lib/libpython3.6m.so
        /home/dp/miniconda3/envs/torch1.4/lib/python3.6/site-packages/numpy/core/lib/libnpymath.a
        ${OpenCV_LIBS}
        )


