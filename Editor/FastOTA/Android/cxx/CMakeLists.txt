cmake_minimum_required(VERSION 3.21)

project("dlstub")

add_library(
        dlstub
        SHARED
        api.cpp)

target_link_libraries(
        dlstub
        PRIVATE
        log
)