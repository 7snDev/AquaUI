#include "button.h"

Button::Button(std::string text) {
  this->lable = new Lable(text);
  this->text = text;
}

void Button::render(Window* window) {
  this->lable->setPos(this->x, this->y);
  this->lable->setText(this->text);
  this->lable->setColor(this->text_Color);
  this->lable->setBackgroundColor(this->background_Color);
  
  this->lable->render(window);
}

void Button::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.x >= this->lable->getX() && event->button.x <= this->lable->getX() + this->lable->getWidth() && event->button.y >= this->lable->getY() && event->button.y <= this->lable->getY() + this->lable->getHeight()) {
      if (this->callback != NULL)
        this->callback();
    }
  }
}

Button::~Button() {
  delete this->lable;
}