cmake_minimum_required(VERSION 3.3)
project(SI_Server)
link_libraries(pthread)
set(SOURCE_FILES
        game/enemy.c
        game/enemy.h
        game/field.c
        game/field.h
        game/game.c
        game/game.h
        game/gameobject.c
        game/gameobject.h
        game/player.c
        game/player.h
        network/net.c
        network/net.h
        network/packer.c
        network/packer.h
        network/packet.c
        network/packet.h
        util/queue.c
        util/queue.h
        main.c util/time.c util/time.h)

add_executable(SI_Server ${SOURCE_FILES})