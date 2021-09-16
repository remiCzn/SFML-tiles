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
    fonts/FreeSans.ttf
    config/editorstate_keybinds
    config/settingsstate_keybinds
    config/gamestate_keybinds
    config/mainmenu_keybinds
    config/supported_keys
    config/window
    images/background/background.png
    images/character/player_sheet.png
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
    src/states/SettingsState.cpp
    src/states/MainMenuState.cpp
    src/states/EditorState.cpp
    src/entities/Entity.cpp
    src/entities/Player.cpp
    src/gui/Button.cpp
    src/gui/DropDownList.cpp
    src/components/MovementComponent.cpp
    src/components/AnimationComponent.cpp
    src/components/HitboxComponent.cpp
    src/tile/Tile.cpp
    src/gui/PauseMenu.cpp
)

target_link_libraries(main sfml-graphics)