cmake_minimum_required(VERSION 3.10)

project(Tile_RPG VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SFML 2.5
    COMPONENTS
        system window graphics network audio REQUIRED
    )

add_executable(main src/main.cpp)

target_link_libraries(main sfml-graphics)