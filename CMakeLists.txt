cmake_minimum_required(VERSION 2.8)
project(tetris)

find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)

# to activate debug mode in qtcreator you have to add
# -DCMAKE_BUILD_TYPE=Debug to the projects/CMake arguments until bug is fixed...
add_definitions(-D_DEBUG)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${SDL_TTF_INCLUDE_DIRS}
                    ${SDL_IMAGE_INCLUDE_DIRS}
                    ${SDL_INCLUDE_DIR})

add_executable(tetris
                           main.c
                           main.h
                           game/game.c
                           game/game.h
                           tools/write_text_on_window/write_text_on_window.c
                           tools/write_text_on_window/write_text_on_window.h)

target_link_libraries(tetris ${SDL_IMAGE_LIBRARIES}
                                                        ${SDL_TTF_LIBRARIES}
                                                        ${SDL_LIBRARY})

target_compile_options(tetris PUBLIC "-O0")

file(COPY font DESTINATION ${CMAKE_BINARY_DIR})
