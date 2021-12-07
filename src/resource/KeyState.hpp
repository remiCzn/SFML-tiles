#ifndef KEYSTATE_HPP
#define KEYSTATE_HPP

class KeyState
{
protected:
    KeyState(){};

    static KeyState *_keystate;

public:
    KeyState(KeyState &other) = delete;
    void operator=(const KeyState &) = delete;
    static KeyState *getInstance();

    bool F3;
    bool PAUSE;
};

#endif