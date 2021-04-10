cmake_minimum_required(VERSION 3.16)
project(typo)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
set(CMAKE_CXX_STANDARD 17)

#find_package(SDL2 REQUIRED)
include_directories(src include ${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})

add_executable(typo src/main.cpp include/window.h src/window.cpp src/TextSprite.cpp include/TextSprite.h include/menu.h src/menu.cpp src/game.cpp include/game.h include/scattered.h src/scattered.cpp src/ScatteredSprite.cpp include/ScatteredSprite.h)
target_link_libraries(typo ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})