cmake_minimum_required(VERSION 3.1)

project(fm_net)

list(APPEND fm_net_src
     epoll.c
     tcp_server.c
     tcp_client.c
     )

add_library(fm_net SHARED ${fm_net_src})
target_link_libraries(fm_net PUBLIC fm_common)