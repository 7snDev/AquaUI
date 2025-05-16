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

char SpishalKey(SDL_Keycode key) {
  switch (key)
  {
  case SDLK_1:
    return '!';
  case SDLK_2:
    return '@';
  case SDLK_3:
    return '#';
  case SDLK_4:
    return '$';
  case SDLK_5:
    return '%';
  case SDLK_6:
    return '^';
  case SDLK_7:
    return '&';
  case SDLK_8:
    return '*';
  case SDLK_9:
    return '(';
  case SDLK_0:
    return ')';
  case SDLK_KP_MINUS:
    return '_';
  case SDLK_KP_EQUALS:
    return '+';
  case SDLK_KP_DIVIDE:
    return '?';
  case SDLK_KP_MULTIPLY:
    return '*';
  case SDLK_KP_PERIOD:
    return '>';
  case SDLK_KP_ENTER:
    return '\n';
  case SDLK_BACKSPACE:
    return '\b';
  case SDLK_DELETE:
    return '\b';
  case SDLK_BACKSLASH:
    return '|';
  case SDLK_SLASH:
    return '?';
  case SDLK_SEMICOLON:
    return ':';
  case SDLK_QUOTE:
    return '"';
  case SDLK_LEFTBRACKET:
    return '{';
  case SDLK_RIGHTBRACKET:
    return '}';
  case SDLK_KP_COMMA:
    return '<';
  case SDLK_KP_0:
    return '0';
  case SDLK_KP_1:
    return '1';
  case SDLK_KP_2:
    return '2';
  case SDLK_KP_3:
    return '3';
  case SDLK_KP_4:
    return '4';
  case SDLK_KP_5:
    return '5';
  case SDLK_KP_6:
    return '6';
  case SDLK_KP_7:
    return '7';
  case SDLK_KP_8:
    return '8';
  case SDLK_KP_9:
    return '9';
  case SDLK_RETURN:
    return '\n';
  case SDLK_TAB:
    return '\t';
  case SDLK_SPACE:
    return ' ';
  default:
    printf("Spishal key not found.\n");
  }
  return '\0';
}

bool isSpishalKey(SDL_Keycode key) {
  switch (key)
  {
  case SDLK_1:
  case SDLK_2:
  case SDLK_3:
  case SDLK_4:
  case SDLK_5:
  case SDLK_6:
  case SDLK_7:
  case SDLK_8:
  case SDLK_9:
  case SDLK_0:
  case SDLK_MINUS:
  case SDLK_EQUALS:
  case SDLK_KP_MINUS:
  case SDLK_KP_PLUS:
  case SDLK_KP_DIVIDE:
  case SDLK_KP_MULTIPLY:
  case SDLK_KP_PERIOD:
  case SDLK_KP_ENTER:
  case SDLK_BACKSPACE:
  case SDLK_DELETE:
  case SDLK_KP_COMMA:
  case SDLK_KP_0:
  case SDLK_KP_1:
  case SDLK_KP_2:
  case SDLK_KP_3:
  case SDLK_KP_4:
  case SDLK_KP_5:
  case SDLK_KP_6:
  case SDLK_KP_7:
  case SDLK_KP_8:
  case SDLK_KP_9:
  case SDLK_RETURN:
  case SDLK_TAB:
  case SDLK_SPACE:
    return true;
  }
  return false;
}

char Key(SDL_Keycode key) {
  if (caps() && isSpishalKey(key)) return SpishalKey(key);
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