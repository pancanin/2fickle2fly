cmake_minimum_required(VERSION 3.5.1)

# Project name and setting language (C or C++)
project(shred2d LANGUAGES CXX)

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

    ${DIR}/osplatform/Time.h
    ${DIR}/osplatform/Time.cpp

    ${DIR}/osplatform/ThreadUtils.h
    ${DIR}/osplatform/ThreadUtils.cpp

    ${DIR}/engine/GameEngine.h
    ${DIR}/engine/GameEngine.cpp

    ${DIR}/engine/drawables/Rect.h
    ${DIR}/engine/drawables/Rect.cpp

    ${DIR}/engine/drawables/Color.h

    ${DIR}/engine/rendering/Renderer.h
    ${DIR}/engine/rendering/Renderer.cpp

    ${DIR}/engine/input/EventEmitter.h
    ${DIR}/engine/input/EventEmitter.cpp

    ${DIR}/engine/math/Vec2.h
    ${DIR}/engine/math/Direction.h

    ${DIR}/engine/drawables/GameObject.h
    ${DIR}/engine/drawables/GameObject.cpp

    ${DIR}/engine/storage/PrimitivesStorage.h
    
    ${DIR}/engine/misc/ForwardIdGenerator.h
    ${DIR}/engine/misc/ID.h

    ${DIR}/engine/physics/collisions/BoundingBox.h
    ${DIR}/engine/physics/collisions/BoundingBox.cpp

    ${DIR}/engine/physics/collisions/CollisionDetector.h
    ${DIR}/engine/physics/collisions/CollisionDetector.cpp

    ${DIR}/engine/physics/collisions/Segmenter.h
    ${DIR}/engine/physics/collisions/Segmenter.cpp
)

# The header files in the current directory and its subdirectories are set as /I (include) compiler option
# For visual studio projects, the added include paths are visible in C/C++ -> General -> Additional Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})

# Add static lib headers for linux
if (UNIX)
include_directories(
    ${DIR}/libs/linux/SDL/include/SDL2
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE ${DIR}/libs/linux/SDL/lib/libSDL2.a
)
endif(UNIX)

# Add static libraries' headers for windows
if (WIN32)
include_directories(
    ${DIR}/libs/win/SDL2-2.28.1/include
    ${DIR}/libs/win/SDL2_ttf-2.20.2/include
    ${DIR}/libs/win/SDL2_mixer-2.6.3/include
    ${DIR}/libs/win/SDL2_image-2.6.3/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${DIR}/libs/win/SDL2-2.28.1/lib/x64/SDL2.lib)

# Post build action to move static libraries dll files to executable's folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/win/SDL2-2.28.1/lib/x64/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif(WIN32)

# Testing binary
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
    ${DIR}/tests/Vec2_test.cpp
    ${DIR}/engine/physics/collisions/BoundingBox.cpp
    ${DIR}/tests/BoundingBox_test.cpp
)

target_include_directories(tests PRIVATE ${DIR})

target_link_libraries(
  tests
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(tests)