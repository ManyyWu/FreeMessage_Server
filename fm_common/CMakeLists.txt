cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 99)

project(fm_common)

include_directories(include)

list(APPEND fm_common_src
     src/common.c
     src/timestamp.c
     src/json.c
     )

add_library(fm_common SHARED ${fm_common_src})
target_link_libraries(fm_common PUBLIC pthread)