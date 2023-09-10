cmake_minimum_required(VERSION 3.5.1)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(2fickle2fly LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
	${DIR}/main.cpp
)

set(CMAKE_CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})
