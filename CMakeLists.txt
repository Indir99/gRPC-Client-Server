cmake_minimum_required(VERSION 3.5)

project(GrpcClientServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Proto)
