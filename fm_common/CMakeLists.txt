cmake_minimum_required(VERSION 3.1)

project(fm_common)

list(APPEND fm_common_src
     common.c
     time.c
     )

add_library(fm_common SHARED ${fm_common_src})
target_link_libraries(fm_common PUBLIC pthread)