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
    config/window.json
    images/character/player_sheet.png
    images/UI/checkx48.png
    resource/fragment_shader.frag
    images/Tiles/Stonex20.png
)

foreach(file ${EXFILES})
    MESSAGE( STATUS "Including " ${file} )
    configure_file(
        src/${file}
        src/${file}
        COPYONLY)
endforeach()

add_executable(main 
    src/headers/headers.cpp
    src/lib/jsoncpp.cpp
    src/resource/algo/Noise.cpp
    src/resource/algo/test/run.cpp
    src/resource/KeyState.cpp

    src/main.cpp
    src/Game.cpp
    src/states/State.cpp
    src/states/GameState.cpp
    src/states/SettingsState.cpp
    src/states/MainMenuState.cpp
    src/states/EditorState.cpp
    src/entities/Entity.cpp
    src/entities/Player.cpp
    src/gui/Button.cpp
    src/gui/DropDownList.cpp
    src/gui/TextureSelector.cpp
    src/resource/GraphicSettings.cpp
    src/gui/CheckBox.cpp
    src/components/MovementComponent.cpp
    src/components/AnimationComponent.cpp
    src/components/HitboxComponent.cpp
    src/components/AttributeComponent.cpp
    src/tile/Tile.cpp
    src/tile/Chunk.cpp
    src/tile/TileMap.cpp
    src/gui/PauseMenu.cpp
    src/gui/PlayerGUI.cpp
    src/gui/progressBar/progressBar.cpp
    src/tile/TileRegistry.cpp
    src/tile/Custom/Stone.cpp
    src/tile/Custom/Dirt.cpp
)

target_link_libraries(main sfml-graphics)