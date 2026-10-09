cmake_minimum_required(VERSION 3.20)

project(Snake
        VERSION 1.0
        LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(snake
        src/game.c
        src/snake.c
)

target_link_libraries(snake PRIVATE raylib)