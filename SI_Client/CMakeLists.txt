cmake_minimum_required(VERSION 3.3)
project(SI_Client)
link_libraries(SDL2)
set(SOURCE_FILES
        engine/engine.c
        engine/engine.h
        util/queue.c
        util/queue.h
        main.c screen/main_menu.c screen/main_menu.h engine/screen.c engine/screen.h)

add_executable(SI_Client ${SOURCE_FILES})