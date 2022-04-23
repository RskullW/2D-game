cmake_minimum_required(VERSION 3.22)
project(escapeFromAfrica)

set(SDL2_INCLUDE_DIR D:/Library/CLionSDL/SDL2-2.0.20/x86_64-w64-mingw32/include)

set(SDL2_LIB_DIR D:/Library/CLionSDL/SDL2-2.0.20/x86_64-w64-mingw32/lib)
set(SDL2_TTF_INCLUDE_DIR D:/Library/CLionSDL/SDL2_ttf-2.0.18/x86_64-w64-mingw32/include)
set(SDL2_TTF_LIB_DIR D:/Library/CLionSDL/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib)

set(SDL2_MIXER_INCLUDE_DIR D:/Library/CLionSDL/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include)
set(SDL2_MIXER_LIB_DIR D:/Library/CLionSDL/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib)

set(SDL2_IMAGE_INCLUDE_DIR D:/Library/CLionSDL/SDL2_image-2.0.5/x86_64-w64-mingw32/include)
set(SDL2_IMAGE_LIB_DIR D:/Library/CLionSDL/SDL2_image-2.0.5/x86_64-w64-mingw32/lib)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

link_directories(${SDL2_IMAGE_LIB_DIR})
link_directories(${SDL2_TTF_LIB_DIR})
link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_MIXER_LIB_DIR})

file(GLOB cpphfiles
        "*.h"
        "*.cpp"
        )

add_executable(escapeFromAfrica ${cpphfiles})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer )