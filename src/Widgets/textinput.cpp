#include "textinput.h"

void TextInput::render(Window* window) {
  this->lable->setPos(this->x, this->y);
  this->lable->setText(this->placeholder);
  this->lable->setColor(this->color);
  this->lable->setBackgroundColor(this->background_Color);
  this->lable->render(window);
}

bool spichal_keys(int sym) {
  std::vector<int> spichal_keys = {
    SDLK_BACKSPACE,
    SDLK_RETURN,
    SDLK_ESCAPE,
    SDLK_TAB,
    SDLK_LSHIFT,
    SDLK_RSHIFT,
    SDLK_LCTRL,
    SDLK_RCTRL,
    SDLK_LALT,
    SDLK_RALT,
    SDLK_CAPSLOCK,
    SDLK_NUMLOCKCLEAR
  };
  for (auto key : spichal_keys)
  {
    if (key == sym)
    {
      return true;
    }
  }
  return false;
}

void TextInput::handleEvent(SDL_Event* event) {
  if (event->type == SDL_KEYDOWN && this->focused)
  {
    switch (event->key.keysym.sym)
    {
    case SDLK_BACKSPACE:
      try {
        this->placeholder.pop_back();
      } catch (const std::exception& e) {
        this->placeholder = "";
      }
      if (this->placeholder == "")
      {
        this->placeholder = " ";
      }
      break;
    case SDLK_RETURN:
      this->setFocused(false);
      break;
    case SDLK_ESCAPE:
      this->setFocused(false);
      break;
    default:
      if (!spichal_keys(event->key.keysym.sym))
      {
        this->placeholder += event->key.keysym.sym;
      }
      break;
    }
  } else if (event->type == SDL_MOUSEBUTTONDOWN)
  {
    if (event->button.x >= this->lable->getX() && event->button.x <= this->lable->getX() + this->lable->getWidth() && event->button.y >= this->lable->getY() && event->button.y <= this->lable->getY() + this->lable->getHeight())
    {
      this->setFocused(true);
    } else {
      this->setFocused(false);
    }
  }
}

TextInput::~TextInput() {
  delete this->lable;
}