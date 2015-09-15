cmake_minimum_required(VERSION 3.3)
project(hahac)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

enable_language(ASM)

set_property(SOURCE asm.S PROPERTY LANGUAGE ASM)

# set(SOURCE_FILES main.c)
# add_executable(hahac ${SOURCE_FILES})

file(GLOB helloworld_SRC
        "*.h"
        "*.c"
        "*.S"
)

add_executable(helloworld ${helloworld_SRC})
