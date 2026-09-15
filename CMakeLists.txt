cmake_minimum_required(VERSION 4.3)
project(OPSYS C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OPSYS
        "Assignments/Programming Assignment 1/example/reboot_monitor.c"
        "Assignments/Programming Assignment 1/example/reboot_test.c"
        "Labs/Lab 2/kernel_read.c"
        "Labs/Lab 2/kmemory.c"
        "Labs/Lab 2/user_read.c"
        "Lectures/Lecture 2/proc_example.c"
        "Lectures/Lecture 2/proc_user.c"
        "Lectures/Lecture 3/kmalloc_test.c"
        "Lectures/Lecture 2/helloWorld.c"
)

# Each C++ source gets its own executable target, since lecture/example files
# commonly each provide their own main().  CONFIGURE_DEPENDS makes CMake notice
# newly added .cpp files the next time CLion reloads or configures the project.
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(CPP_SOURCE IN LISTS CPP_SOURCES)
    file(RELATIVE_PATH CPP_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CPP_SOURCE}")
    string(REPLACE ".cpp" "" CPP_TARGET_SUFFIX "${CPP_RELATIVE_PATH}")
    string(REGEX REPLACE "[^A-Za-z0-9_]" "_" CPP_TARGET_SUFFIX "${CPP_TARGET_SUFFIX}")
    add_executable("cpp_${CPP_TARGET_SUFFIX}" "${CPP_SOURCE}")
endforeach()
