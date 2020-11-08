cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 99)

project(test)

include_directories(.)

list(APPEND test_src
     cmockery.c
     run_test.c
     test-util.c
     test-thread.c
     test-lock.c
     test-list.c
     test-map.c
     test-tcp_server.c
     test-msgq.c
     )

add_executable(test ${test_src})

target_link_libraries(test PRIVATE fm_common fm_kernel uv)
