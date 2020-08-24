cmake_minimum_required(VERSION 3.1)

project(fm_kernel)

list(APPEND fm_kernel_src
     thread.c
     )

add_library(fm_kernel SHARED ${fm_kernel_src})
target_link_libraries(fm_kernel PUBLIC fm_common)
