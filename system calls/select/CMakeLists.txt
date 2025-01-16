cmake_minimum_required(VERSION 3.10)
project(SelectExample)

set(CMAKE_CXX_STANDARD 17)

# Add executables for client, server, and main
add_executable(client_select client_select.cpp)
add_executable(server_select server_select.cpp)
add_executable(main_select main_select.cpp)

# Custom targets to execute programs
add_custom_target(run_server
    COMMAND ./server_select
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS server_select
)

add_custom_target(run_clients
    COMMAND ./main_select
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS main_select client_select
)
