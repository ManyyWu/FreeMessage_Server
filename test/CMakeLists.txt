cmake_minimum_required(VERSION 3.1)

project(test)

include_directories(.)

list(APPEND test_src
    cmockery.c
    run_test.c
    test-util.c
    test-thread.c
    test-lock.c
    test-get-time.c
    )

add_executable(test ${test_src})

target_link_libraries(test PRIVATE fm_common fm_kernel)
