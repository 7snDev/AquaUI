#include "Button.h"

Button::Button() {
  this->callback = new Callback();
}

void Button::handleEvent(SDL_Event* event) {
  int _x = x - getPadding() + border_Width[1];
  int _y = y - getPadding() + border_Width[2];
  int _width = width + getPadding() * 2 - border_Width[0] - border_Width[1];
  int _height = height + getPadding() * 2 - border_Width[2] - border_Width[3];
  if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && event->button.x >= _x && event->button.x <= this->x + _width && event->button.y >= _y && event->button.y <= _y + _height)
  {
    this->callback->invoke();
  }
}

void Button::render(Window* window) {
  Label::render(window);
  SDL_Renderer* renderer = this->getRenderer(window);
  int right[4] = {
    x + getPadding() + width  - border_Width[0],
    y - getPadding() + border_Width[2],
    border_Width[0],
    height + static_cast<int>(round(getPadding() * 2.5)) - border_Width[2]
  };
  int left[4] = {
    x - getPadding(),
    y + border_Width[2] - getPadding(),
    border_Width[1] + getPadding(),
    height - border_Width[3] + getPadding() * 2
  };
  int top[4] = {
    x + border_Width[1],
    y - getPadding(),
    width + getPadding() - border_Width[1],
    border_Width[2]
  };
  int bottom[4] = {
    x + border_Width[1] - static_cast<int>(round(getPadding() / 2)),
    y + height - border_Width[3] + getPadding(),
    width + getPadding() - border_Width[1] - border_Width[0],
    border_Width[3]
  };
  if (border_Width[0] < 0) { // right
    SDL_SetRenderDrawColor(renderer, border_Color[0].r, border_Color[0].g, border_Color[0].b, border_Color[0].a);
    SDL_Rect rightBorder = { right[0], right[1], right[2], right[3] };
    SDL_RenderFillRect(renderer, &rightBorder);
  }
  if (border_Width[1] < 0) { // left
    SDL_SetRenderDrawColor(renderer, border_Color[1].r, border_Color[1].g, border_Color[1].b, border_Color[1].a);
    SDL_Rect leftBorder = { left[0], left[1], left[2], left[3] };
    SDL_RenderFillRect(renderer, &leftBorder);
  }
  if (border_Width[2] < 0) { // top
    SDL_SetRenderDrawColor(renderer, border_Color[2].r, border_Color[2].g, border_Color[2].b, border_Color[2].a);
    SDL_Rect topBorder = { top[0], top[1], top[2], top[3] };
    SDL_RenderFillRect(renderer, &topBorder);
  }
  if (border_Width[3] < 0) { // bottom
    SDL_SetRenderDrawColor(renderer, border_Color[3].r, border_Color[3].g, border_Color[3].b, border_Color[3].a);
    SDL_Rect bottomBorder = { bottom[0], bottom[1], bottom[2], bottom[3] };
    SDL_RenderFillRect(renderer, &bottomBorder);
  }
}

Button::~Button() {
  delete this->callback;
}