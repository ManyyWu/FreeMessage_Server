cmake_minimum_required(VERSION 3.1)

project(fm_kernel)

include_directories(include)

list(APPEND fm_kernel_src
     src/msg.c
     src/thread.c
     src/msg_queue.c
     )

add_library(fm_kernel SHARED ${fm_kernel_src})
target_link_libraries(fm_kernel PUBLIC fm_common)
