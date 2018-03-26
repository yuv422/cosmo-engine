cmake_minimum_required(VERSION 3.5)
project(cosmo_engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cosmo_engine_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

set(SOURCE_FILES
        src/actor.c
        src/actor.h
        src/main.c
        src/player.c
        src/player.h src/game.h src/game.c src/palette.c src/palette.h src/util.h src/util.c
        src/map.c src/map.h src/defines.h src/input.c src/input.h src/dialog.c src/dialog.h src/tile.c src/tile.h
        src/files/vol.c src/files/vol.h src/files/file.c src/files/file.h src/video.c src/video.h
        src/sound/music.c src/sound/music.h src/backdrop.c src/backdrop.h src/save.c src/save.h
        src/status.c src/status.h src/actor_worktype.c src/actor_worktype.h src/actor_worktype.c src/actor_worktype.h
        src/effects.c src/effects.h src/actor_collision.c src/actor_collision.h src/actor_toss.c src/actor_toss.h
        src/font.c src/font.h src/sound/sfx.c src/sound/sfx.h src/sound/audio.c src/sound/audio.h
        src/platforms.c src/platforms.h src/sound/opl.c src/sound/opl.h src/fullscreen_image.c src/fullscreen_image.h
        src/cartoon.c src/cartoon.h src/b800_font.h src/config.c src/config.h src/high_scores.c src/high_scores.h
        src/demo.c src/demo.h src/b800.c src/b800.h)

include_directories(src)

add_executable(cosmo_engine ${SOURCE_FILES})

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    TARGET_LINK_LIBRARIES(cosmo_engine ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    TARGET_LINK_LIBRARIES(cosmo_engine dl m ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    TARGET_LINK_LIBRARIES(cosmo_engine ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
