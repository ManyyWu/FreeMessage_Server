cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 99)

project(fm_net)

add_subdirectory(libuv)

include_directories(include)
include_directories(libuv/include)

list(APPEND fm_net_src
     src/net_kernel.c
     src/io_context.c
     src/io_service.c
     src/tcp_server.c
     src/tcp_client.c
     )

add_library(fm_net SHARED ${fm_net_src})
target_link_libraries(fm_net PUBLIC fm_common uv)