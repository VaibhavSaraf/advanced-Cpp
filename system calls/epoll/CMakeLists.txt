# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(EpollSelectExample)

set(CMAKE_CXX_STANDARD 17)

# Add executables for client, server, and main
add_executable(client client.cpp)
add_executable(server server.cpp)
add_executable(main main.cpp)

# Custom targets to execute programs
add_custom_target(run_server
    COMMAND ./server
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS server
)

add_custom_target(run_clients
    COMMAND ./main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS main client
)

