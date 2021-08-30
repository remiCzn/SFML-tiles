cmake_minimum_required(VERSION 3.10)

project(Tile_RPG VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SFML 2.5
    COMPONENTS
        system window graphics network audio REQUIRED
    )

set(EXFILES
    fonts/Dosis-Light.ttf
    config/gamestate_keybinds
    config/mainmenu_keybinds
    config/supported_keys
    config/window
)

foreach(file ${EXFILES})
    MESSAGE( STATUS "Including " ${file} )
    configure_file(
        src/${file}
        ${file}
        COPYONLY)
endforeach()

add_executable(main 
    src/main.cpp
    src/Game.cpp
    src/State.cpp
    src/states/GameState.cpp
    src/entities/Entity.cpp
    src/states/MainMenuState.cpp
    src/resource/Button.cpp
)

target_link_libraries(main sfml-graphics)