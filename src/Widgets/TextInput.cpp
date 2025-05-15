#include "TextInput.h"

std::set<SDL_Keycode> Keys;
bool isPressedCaps = false;

bool caps() {
  if (isPressedCaps ||
    (Keys.find(SDLK_CAPSLOCK) != Keys.end()) ||
    (Keys.find(SDLK_LSHIFT) != Keys.end()) ||
    (Keys.find(SDLK_RSHIFT) != Keys.end()))
    return true;
  else
    return false;
}

bool isSpishalKey(SDL_Keycode key) {
  
}

char SpishalKey(SDL_Keycode key) {
  
}

char Key(SDL_Keycode key) {
  if (isSpishalKey(key)) return SpishalKey(key);
  else {
    if (caps())
      return toupper((char)key);
    return tolower((char)key);
  }
}

bool isSpishal(SDL_Keycode key) {
  if (
    key == SDLK_BACKSPACE ||
    key == SDLK_TAB ||
    key == SDLK_RETURN ||
    key == SDLK_LSHIFT ||
    key == SDLK_RSHIFT ||
    key == SDLK_LCTRL ||
    key == SDLK_RCTRL ||
    key == SDLK_LALT ||
    key == SDLK_RALT ||
    key == SDLK_CAPSLOCK ||
    key == SDLK_LGUI ||
    key == SDLK_RGUI ||
    key == SDLK_KP_ENTER
  )
    return true;
  return false;
}

void TextInput::handleEvent(SDL_Event* event) {
  int _x = x - getPadding() + border_Width[1];
  int _y = y - getPadding() + border_Width[2];
  int _width = width + getPadding() * 2 - border_Width[0] - border_Width[1];
  int _height = height + getPadding() * 2 - border_Width[2] - border_Width[3];
  if (event->type == SDL_MOUSEBUTTONDOWN)
  {
    if (event->button.button == SDL_BUTTON_LEFT && event->button.x >= _x && event->button.x <= this->x + _width && event->button.y >= _y && event->button.y <= _y + _height)
    {
      this->callback->invoke();
      this->isFocused = true;
    } else {
      this->isFocused = false;
    }
  } else if (event->type == SDL_MOUSEMOTION)
  {
    if (event->motion.x >= _x && event->motion.x <= this->x + _width && event->motion.y >= _y && event->motion.y <= _y + _height)
      this->isHovered = true;
    else
      this->isHovered = false;
  } else if (event->type == SDL_KEYDOWN && this->isFocused)
  {
    Keys.insert(event->key.keysym.sym);
    SDL_Keycode key = event->key.keysym.sym;
    if (key == SDLK_BACKSPACE || key == SDLK_DELETE)
    {
      if (text.length() > 1)
        text.pop_back();
      else if (text.length() == 1)
        text = " ";
    } else {
      if (!isSpishal(key))
        text.push_back(Key(key));
    }
    this->onChangeCallback->invoke();
  } else if (event->type == SDL_KEYUP)
  {
    if (event->key.keysym.sym == SDLK_CAPSLOCK)
      isPressedCaps = !isPressedCaps;
    Keys.erase(event->key.keysym.sym);
  }
}