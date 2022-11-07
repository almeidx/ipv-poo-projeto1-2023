cmake_minimum_required(VERSION 3.23)
project(ipv_poo_projeto1_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ipv_poo_projeto1_2022
        User.cpp
        User.h
        UserPermissions.h
        main.cpp)
