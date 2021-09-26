cmake_minimum_required(VERSION 3.20)
project(coms C)

set(CMAKE_C_STANDARD 11)

add_executable(coms main.c ordercache/order_cache.c ordercache/order_cache.h lib/seethe.h securitycache/security_cache.c securitycache/security_cache.h utils/dt_utils.c utils/dt_utils.h)
