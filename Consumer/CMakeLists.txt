cmake_minimum_required(VERSION 3.13)
project(Consumer C)

set(CMAKE_C_STANDARD 11)

add_executable(Consumer
        main_consumer.c)

target_link_libraries(Consumer "-lrt")