#include "lable.h"

Lable::Lable(std::string text, int x, int y, SDL_Color text_Color, SDL_Color background_Color, TTF_Font* font) {
  this->text = text;
  this->x = x;
  this->y = y;
  this->text_Color = text_Color;
  this->background_Color = background_Color;
  this->font = font;
}

void Lable::render(SDL_Renderer* renderer) {
  if (this->font == NULL)
    return;
  SDL_Surface* surface;
  if (this->background_Color.a == 0) {
    surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->text_Color);
  }
  else {
    surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->text_Color, this->background_Color);
  }
  
  if (surface == NULL)
  {
    printf("TTF_RenderText_Shaded failed: %s\n", TTF_GetError());
    throw std::runtime_error(TTF_GetError());
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  SDL_Rect rect = {this->x, this->y, surface->w, surface->h};
  SDL_SetRenderDrawColor(renderer, this->background_Color.r, this->background_Color.g, this->background_Color.b, this->background_Color.a);
  SDL_RenderFillRect(renderer, &rect);
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}