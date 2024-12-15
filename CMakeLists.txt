cmake_minimum_required(VERSION 3.10)

project(TileWander2 LANGUAGES CXX)

#[[
add_library(info info.cpp)
target_include_directories(info PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_library(Players src/Players.cpp)
target_include_directories(Players PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_library(World src/World.cpp)
target_include_directories(World PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(TileWander2 main.cpp)
target_link_libraries(TileWander2 PUBLIC info Players World)
#]]

add_executable(TileWander2 main.cpp info.cpp src/Players.cpp src/World.cpp)
target_include_directories(TileWander2 PUBLIC "${PROJECT_SOURCE_DIR}/include")
