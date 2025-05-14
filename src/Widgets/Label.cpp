#include "Label.h"

void Label::render(Window* window) {
  if (this->font == NULL) {
    this->font = window->getFont();
  }
  SDL_Surface* surface;
  if (this->background_Color.a == 0) {
    surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->text_Color, window->getBackgroundColor());
  }
  else {
    surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->text_Color, this->background_Color);
  }
  
  if (surface == NULL)
  {
    printf("TTF_RenderText_Shaded failed: %s\n", TTF_GetError());
    throw std::runtime_error(TTF_GetError());
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->getRenderer(window), surface);
  SDL_Rect rect = {this->x, this->y, surface->w, surface->h};
  this->width = surface->w;
  this->height = surface->h;
  SDL_SetRenderDrawColor(this->getRenderer(window), this->background_Color.r, this->background_Color.g, this->background_Color.b, this->background_Color.a);
  SDL_RenderFillRect(this->getRenderer(window), &rect);
  SDL_RenderCopy(this->getRenderer(window), texture, NULL, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}