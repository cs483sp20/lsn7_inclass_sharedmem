cmake_minimum_required(VERSION 3.13)
project(Producer C)

set(CMAKE_C_STANDARD 11)

add_executable(Producer
        main_producer.c)

target_link_libraries(Producer "-lrt")