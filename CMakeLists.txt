cmake_minimum_required(VERSION 4.2)
project(CulturalAgenda C)

set(CMAKE_C_STANDARD 23)

add_executable(CulturalAgenda main.c
        eventlibrary.h
        validation.c
        validation.h
        eventlibrary.c)
