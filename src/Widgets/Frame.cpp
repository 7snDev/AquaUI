#include "Frame.h"

void Frame::setSrc(std::string src) {
  this->src = src;
  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    throw std::runtime_error(IMG_GetError());
  this->surface = IMG_Load(src.c_str());
  if (this->surface == nullptr)
    throw std::runtime_error(IMG_GetError());
}

void Frame::render(Window* window) {
  if (this->surface == nullptr && this->texture == nullptr && this->src == "")
    throw std::runtime_error("Texture and surface and src is null");
  if (this->texture == nullptr) {
    if (this->surface == nullptr)
      throw std::runtime_error("Texture and surface is null");
    this->texture = SDL_CreateTextureFromSurface(this->getRenderer(window), this->surface);
  }
  if (this->texture == nullptr)
    throw std::runtime_error(SDL_GetError());
  
  this->rect = {this->x, this->y, this->width, this->height};
  SDL_RenderCopy(this->getRenderer(window), this->texture, nullptr, &this->rect);
}

void Frame::setAutoSize() {
  if (this->surface == nullptr)
    throw std::runtime_error("Surface is null");
  
  this->width = this->surface->w;
  this->height = this->surface->h;
}

Frame::~Frame() {
  SDL_FreeSurface(this->surface);
  SDL_DestroyTexture(this->texture);
}

void Frame::handleEvent(SDL_Event* event) {
  int _x = x;
  int _y = y;
  int _width = width;
  int _height = height;
  if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && event->button.x >= _x && event->button.x <= this->x + _width && event->button.y >= _y && event->button.y <= _y + _height)
  {
    this->callback->invoke();
  }
}