cmake_minimum_required(VERSION 3.16)
project(ipv_poo_projeto1_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ipv_poo_projeto1_2022
        Fabrica.cpp
        Fabrica.h
        Motor.cpp
        Motor.h
        Ponto.h
        Sensor.h
        Sensor.cpp
        tinyxml2.cpp
        tinyxml2.h
        User.cpp
        User.h
        Uteis.h
        main.cpp)
