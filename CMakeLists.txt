cmake_minimum_required(VERSION 3.23)
project(ipv_poo_projeto1_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ipv_poo_projeto1_2022
        EstadoMotor.h
        Fabrica.cpp
        Fabrica.h
        Motor.cpp
        Motor.h
        Sensor.h
        Sensor.cpp
        User.cpp
        User.h
        UserPermissions.h
        main.cpp)
