#include "KeyState.hpp"

KeyState* KeyState::_keystate = nullptr;

KeyState* KeyState::getInstance() {
    if(_keystate == nullptr) {
        _keystate = new KeyState();
    }
    return _keystate;
}

