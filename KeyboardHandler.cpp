#include "KeyboardHandler.h"

void KeyboardHandler::handleKeyboardEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        keyState[event.key.key] = PRESSED;
    }
    else if (event.type == SDL_EVENT_KEY_UP) {
        keyState[event.key.key] = RELEASED;
    }
}

bool KeyboardHandler::isPressed(SDL_Keycode keyCode) {
    return keyState[keyCode] == PRESSED;
}

bool KeyboardHandler::isPressedThisFrame(SDL_Keycode keyCode) {
    return keyState[keyCode] == PRESSED && previousKeyState[keyCode] == RELEASED;
}

bool KeyboardHandler::isReleased(SDL_Keycode keyCode) {
    return keyState[keyCode] == RELEASED;
}

bool KeyboardHandler::isReleasedThisFrame(SDL_Keycode keyCode) {
    return keyState[keyCode] == RELEASED && previousKeyState[keyCode] == PRESSED;
}

void KeyboardHandler::update()
{
    previousKeyState = keyState;
}