cmake_minimum_required(VERSION 3.8)
project(cosmo_engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
SET(SDL_VERSION "SDL2")
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
SET(SDL_LIBS "${SDL2_LIBRARIES} -l${SDL2MIXER_LIBRARIES}")

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
        src/cartoon.c src/cartoon.h)

include_directories(src)

add_executable(cosmo_engine ${SOURCE_FILES})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    TARGET_LINK_LIBRARIES(cosmo_engine -L/usr/local/lib ${SDL_LIBS} -Wl,-framework,Cocoa)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    TARGET_LINK_LIBRARIES(cosmo_engine dl ${SDL_LIBS} )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")