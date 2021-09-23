cmake_minimum_required(VERSION 3.20)
project(coms C)

set(CMAKE_C_STANDARD 11)

add_executable(coms main.c ordercache/order_cache.c ordercache/order_cache.h)
