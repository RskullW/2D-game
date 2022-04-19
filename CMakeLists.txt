cmake_minimum_required(VERSION 3.22)
project(escapeFromAfrica)

#set(project_SOURCE_DIR D:/ProjectCLion(c++)/escapeFromAfrica)
set(SDL2_INCLUDE_DIR D:/Library/CLionSDL/SDL2-2.0.20/x86_64-w64-mingw32/include)
set(SDL2_LIB_DIR D:/Library/CLionSDL/SDL2-2.0.20/x86_64-w64-mingw32/lib)

set(SDL2_TTF_INCLUDE_DIR D:/Library/CLionSDL/SDL2_ttf-2.0.18/x86_64-w64-mingw32/include)
set(SDL2_TTF_LIB_DIR D:/Library/CLionSDL/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib)

set(SDL2_INCLUDE_DIR D:/Library/CLionSDL/SDL2-2.0.20/x86_64-w64-mingw32/include)
set(SDL2_LIB_DIR D:/Library/CLionSDL/SDL2-2.0.20/x86_64-w64-mingw32/lib)

set(SDL2_MIXER_INCLUDE_DIR D:/Library/CLionSDL/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include)
set(SDL2_MIXER_LIB_DIR D:/Library/CLionSDL/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib)

set(SDL2_IMAGE_INCLUDE_DIR D:/Library/CLionSDL/SDL2_image-2.0.5/x86_64-w64-mingw32/include)
set(SDL2_IMAGE_LIB_DIR D:/Library/CLionSDL/SDL2_image-2.0.5/x86_64-w64-mingw32/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

link_directories(${SDL2_IMAGE_LIB_DIR})
link_directories(${SDL2_TTF_LIB_DIR})
link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_MIXER_DIR})


file(GLOB cpphfiles
        "*.h"
        "*.cpp"
        )

add_executable(escapeFromAfrica ${cpphfiles})

#add_executable(escapeFromAfrica main.cpp Animation.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#
#include_directories(${SDL2_INCLUDE_DIR}
#        ${SDL2_IMAGE_INCLUDE_DIR}
#        ${SDL2_TTF_INCLUDE_DIR}
#        ${SDL2_MIXER_INCLUDE_DIR})
#
#
#target_link_libraries(escapeFromAfrica ${SDL2_LIBRARY}
#        ${SDL2_IMAGE_LIBRARIES}
#        ${SDL2_TTF_LIBRARIES}
#        ${SDL2_MIXER_INCLUDE_DIR} -lmingw32 -lSDL2main -lSDL2 -mwindows)
