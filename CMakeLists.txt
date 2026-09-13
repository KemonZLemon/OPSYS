cmake_minimum_required(VERSION 4.3)
project(OPSYS C)

set(CMAKE_C_STANDARD 11)

add_executable(OPSYS
        "Assignments/Programming Assignment 1/example/reboot_monitor.c"
        "Assignments/Programming Assignment 1/example/reboot_test.c"
        "Labs/Lab 2/kernel_read.c"
        "Labs/Lab 2/kmemory.c"
        "Labs/Lab 2/user_read.c"
        "Lectures/Lecture 2/proc_example.c"
        "Lectures/Lecture 2/proc_user.c"
        "Lectures/Lecture 3/kmalloc_test.c")
