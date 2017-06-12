cmake_minimum_required(VERSION 3.5)
project(Rosette)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(ALLEGRO_LIB C:/Users/Hash/ClionProjects/Rosette/deps/allegro/lib/liballegro_monolith-debug.dll.a)

set(SOURCE_FILES rosette.c fw.c global.c etatjeu.c jeu.c Util/hex.c souris.c transition.c board.c logic.c intro.c Util/data_struct.c hud.c view.c menu.c menu_principal.c UI/circle_container.c UI/circle_container.h UI/button.c UI/button.h clavier.c clavier.h aide.c aide.h)
add_executable(Rosette ${SOURCE_FILES})
include_directories(deps/allegro/include)
link_directories(${ALLEGRO_LIB_PATH})

target_link_libraries(Rosette ${ALLEGRO_LIB})