cmake_minimum_required(VERSION 3.1)

project(free_message)

include_directories(.)

add_subdirectory(fm_common)
add_subdirectory(fm_net)
add_subdirectory(fm_kernel)
add_subdirectory(fm_rpc)
add_subdirectory(fm_lua)
add_subdirectory(fm_db)
add_subdirectory(fm_dbs)
add_subdirectory(fm_cs)
add_subdirectory(fm_ss)
add_subdirectory(fm_plat)
add_subdirectory(fm_router)
add_subdirectory(fm_client)
add_subdirectory(test)
