#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <map>

class KeyboardHandler {
public:
    void handleKeyboardEvent(const SDL_Event& event);

    bool isPressed(SDL_Keycode keyCode);
    bool isPressedThisFrame(SDL_Keycode keyCode);

    bool isReleased(SDL_Keycode keyCode);
    bool isReleasedThisFrame(SDL_Keycode keyCode);

    void update();

private:
    std::map<SDL_Keycode, int> keyState;
    std::map<SDL_Keycode, int> previousKeyState;

    const int PRESSED = 1;
    const int RELEASED = 0;
};