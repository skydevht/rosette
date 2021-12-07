cmake_minimum_required(VERSION 3.5)
find_package(PkgConfig REQUIRED)

project(Rosette)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(ROSETTE_SRCS rosette.c fw.c global.c etatjeu.c jeu.c Util/hex.c souris.c transition.c board.c logic.c intro.c Util/data_struct.c hud.c view.c menu.c menu_principal.c UI/circle_container.c UI/circle_container.h UI/button.c UI/button.h clavier.c clavier.h aide.c aide.h)

file(GLOB ROSETTE_DATA data/*)

set(ROSETTE_REL_DATA)
foreach(data ${ROSETTE_DATA})
    file(RELATIVE_PATH relpath "${CMAKE_CURRENT_SOURCE_DIR}" "${data}")
    list(APPEND ROSETTE_REL_DATA "${relpath}")
endforeach(data)

if(APPLE)
    set(ROSETTE_EXECUTABLE_TYPE MACOSX_BUNDLE)
else(APPLE)
    set(ROSETTE_EXECUTABLE_TYPE "${EXECUTABLE_TYPE}")
endif(APPLE)

add_executable(rosette ${ROSETTE_SRCS} ${ROSETTE_DATA})

add_custom_command(TARGET rosette POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:rosette>/data)

pkg_check_modules(ALLEGRO5 REQUIRED allegro-5
                                    allegro_acodec-5 
                                    allegro_audio-5 
                                    allegro_font-5 
                                    allegro_ttf-5
                                    allegro_main-5
                                    allegro_image-5 
                                    allegro_primitives-5)
target_link_libraries(rosette ${ALLEGRO5_LINK_LIBRARIES})
target_include_directories(rosette PUBLIC ${ALLEGRO5_INCLUDE_DIRS})


set_source_files_properties(${ROSETTE_DATA} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources/data")