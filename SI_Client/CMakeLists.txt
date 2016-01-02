cmake_minimum_required(VERSION 3.3)
project(SI_Client)
link_libraries(pthread)
set(SOURCE_FILES
    util/queue.c
    util/queue.h
    main.c)

add_executable(SI_Client ${SOURCE_FILES})