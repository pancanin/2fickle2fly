cmake_minimum_required(VERSION 3.5.1)

# Project name and setting language (C or C++)
project(2fickle2fly LANGUAGES CXX)

# Compile with the C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED YES)

# Setting up cmake variables
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} 
	${DIR}/main.cpp
	# Add source and header files below

    # SDL API
    ${DIR}/api/sdl/SDLInitiator.h
    ${DIR}/api/sdl/SDLInitiator.cpp

    ${DIR}/api/sdl/errors/SDLError.h
    ${DIR}/api/sdl/errors/SDLError.cpp

    ${DIR}/api/sdl/window/Window.h
    ${DIR}/api/sdl/window/Window.cpp
)

# The header files in the current directory and its subdirectories are set as /I (include) compiler option
# For visual studio projects, the added include paths are visible in C/C++ -> General -> Additional Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})

# Add static libraries' headers
include_directories(
    ${DIR}/libs/SDL2-2.28.1/include
    ${DIR}/libs/SDL2_ttf-2.20.2/include
    ${DIR}/libs/SDL2_mixer-2.6.3/include
    ${DIR}/libs/SDL2_image-2.6.3/include
)

link_directories(
    ${DIR}/libs/SDL2-2.28.1/lib/x64
    ${DIR}/libs/SDL2_ttf-2.20.2/lib/x64
    ${DIR}/libs/SDL2_mixer-2.6.3/lib/x64
    ${DIR}/libs/SDL2_image-2.6.3/lib/x64
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${DIR}/libs/SDL2-2.28.1/lib/x64/SDL2.lib)

# Post build action to move static libraries dll files to executable's folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2-2.28.1/lib/x64/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})