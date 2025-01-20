cmake_minimum_required(VERSION 3.30)
project(dealership C)

set(CMAKE_C_STANDARD 11)

add_executable(dealership main.c car.c car.h client.c client.h)
