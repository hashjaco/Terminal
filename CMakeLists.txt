cmake_minimum_required(VERSION 3.12)
project(csc415_p3_hashjaco C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(csc415_p3_hashjaco
        shellcommands.h
        myshell.c)


