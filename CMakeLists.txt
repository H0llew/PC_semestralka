cmake_minimum_required(VERSION 3.17)
project(PC_semestralka C)

set(CMAKE_C_STANDARD 90)

add_executable(PC_semestralka main.c console_input.h console_input.c nodes_reader.h reader_utils.h nodes_reader.c reader_utils.c edges_reader.c edges_reader.h)