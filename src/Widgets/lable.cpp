#include "lable.h"

void Lable::render(Window* _window) {
  if (this->font == NULL) {
    this->font = _window->getFont();
  }
  SDL_Surface* surface;
  if (this->background_Color.a == 0) {
    surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->text_Color, _window->getBackgroundColor());
  }
  else {
    surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->text_Color, this->background_Color);
  }
  
  if (surface == NULL)
  {
    printf("TTF_RenderText_Shaded failed: %s\n", TTF_GetError());
    throw std::runtime_error(TTF_GetError());
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(_window->getRednerer(), surface);
  SDL_Rect rect = {this->x, this->y, surface->w, surface->h};
  this->Width = surface->w;
  this->Height = surface->h;
  SDL_SetRenderDrawColor(_window->getRednerer(), this->background_Color.r, this->background_Color.g, this->background_Color.b, this->background_Color.a);
  SDL_RenderFillRect(_window->getRednerer(), &rect);
  SDL_RenderCopy(_window->getRednerer(), texture, NULL, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}