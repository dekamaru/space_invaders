cmake_minimum_required(VERSION 3.3)
project(SI_Client)
link_libraries(SDL2 SDL2_ttf SDL2_image pthread)
set(SOURCE_FILES
        engine/engine.c
        engine/engine.h
        util/queue.c
        util/queue.h
        main.c screen/main_menu.c screen/main_menu.h engine/screen.c engine/screen.h util/font.c util/font.h engine/assets.c engine/assets.h engine/renderer.c engine/renderer.h engine/network.c engine/network.h screen/game.c screen/game.h util/time.c util/time.h screen/field.c screen/field.h game/player.c game/player.h game/enemy.c game/enemy.h game/gameobject.c game/gameobject.h screen/connect.c screen/connect.h screen/gameover.c screen/gameover.h)

add_executable(SI_Client ${SOURCE_FILES})
add_custom_target(valgrind /usr/bin/valgrind ${PROJECT_BINARY_DIR}/SI_Client)