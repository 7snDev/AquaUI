#include "Label.h"

void Label::render(Window* window) {
  if (this->font == NULL) {
    this->font = window->getFont();
  }
  SDL_Color _Color, _background_Color;
  if (this->isHovered)
  {
    _Color = this->getHoverColor();
    _background_Color = this->getHoverBackgroundColor();
  } else {
    _Color = this->getColor();
    _background_Color = this->getBackgroundColor();
  }
  SDL_Surface* surface;
  if (this->background_Color.a == 0) {
    surface = TTF_RenderText_Blended(this->font, this->text.c_str(), _Color);
  }
  else {
    surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), _Color, _background_Color);
  }
  
  if (surface == NULL)
  {
    printf("TTF_RenderText_Shaded failed: %s\n", TTF_GetError());
    throw std::runtime_error(TTF_GetError());
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->getRenderer(window), surface);
  SDL_Rect paddingRect = {this->x - this->padding, this->y - this->padding, surface->w + this->padding + this->padding, surface->h + this->padding + this->padding};
  SDL_Rect rect;
  if (this->alignment == Alignment::LEFT)
    rect = {this->x - this->padding + 6, this->y, surface->w, surface->h};
  else if (this->alignment == Alignment::RIGHT)
    rect = {this->x + this->padding - 6, this->y, surface->w, surface->h};
  else
    rect = {this->x, this->y, surface->w, surface->h};
  
  
  this->width = surface->w;
  this->height = surface->h;
  SDL_SetRenderDrawColor(this->getRenderer(window), _background_Color.r, _background_Color.g, _background_Color.b, _background_Color.a);
  SDL_RenderFillRect(this->getRenderer(window), &paddingRect);
  SDL_SetRenderDrawColor(this->getRenderer(window), _Color.r, _Color.g, _Color.b, _Color.a);
  if (_background_Color.a > 0)
  {
    SDL_SetRenderDrawBlendMode(this->getRenderer(window), SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(this->getRenderer(window), &rect);
  }
  
  SDL_RenderCopy(this->getRenderer(window), texture, NULL, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
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
  if (border_Width[0] < 0) {
    SDL_SetRenderDrawColor(this->getRenderer(window), border_Color[0].r, border_Color[0].g, border_Color[0].b, border_Color[0].a);
    SDL_Rect rightBorder = { right[0], right[1], right[2], right[3] };
    SDL_RenderFillRect(this->getRenderer(window), &rightBorder);
  }
  if (border_Width[1] < 0) {
    SDL_SetRenderDrawColor(this->getRenderer(window), border_Color[1].r, border_Color[1].g, border_Color[1].b, border_Color[1].a);
    SDL_Rect leftBorder = { left[0], left[1], left[2], left[3] };
    SDL_RenderFillRect(this->getRenderer(window), &leftBorder);
  }
  if (border_Width[2] < 0) {
    SDL_SetRenderDrawColor(this->getRenderer(window), border_Color[2].r, border_Color[2].g, border_Color[2].b, border_Color[2].a);
    SDL_Rect topBorder = { top[0], top[1], top[2], top[3] };
    SDL_RenderFillRect(this->getRenderer(window), &topBorder);
  }
  if (border_Width[3] < 0) {
    SDL_SetRenderDrawColor(this->getRenderer(window), border_Color[3].r, border_Color[3].g, border_Color[3].b, border_Color[3].a);
    SDL_Rect bottomBorder = { bottom[0], bottom[1], bottom[2], bottom[3] };
    SDL_RenderFillRect(this->getRenderer(window), &bottomBorder);
  }
}

void Label::setPadding(int padding_) {
  this->padding = padding_;
}

void Label::handleEvent(SDL_Event* event) {
  int _x = x - getPadding() + border_Width[1];
  int _y = y - getPadding() + border_Width[2];
  int _width = width + getPadding() * 2 - border_Width[0] - border_Width[1];
  int _height = height + getPadding() * 2 - border_Width[2] - border_Width[3];
  if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && event->button.x >= _x && event->button.x <= this->x + _width && event->button.y >= _y && event->button.y <= _y + _height)
  {
    this->callback->invoke();
  } else if (event->type == SDL_MOUSEMOTION)
  {
    if (event->motion.x >= _x && event->motion.x <= this->x + _width && event->motion.y >= _y && event->motion.y <= _y + _height)
      this->isHovered = true;
    else
      this->isHovered = false;
  }
}