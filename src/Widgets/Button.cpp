#include "Button.h"

class Callback {
  private:
    std::function<void()> callable;
  public:
    Callback() = default;
    template<typename Func, typename... Args>
    void bind(Func&& func, Args&&... args) {
      callable = [f = std::forward<Func>(func),
        tpl = std::make_tuple(std::forward<Args>(args)...)]() mutable {
        std::apply(f, tpl);
      };
    }
    void invoke() {
      if (callable) {
        callable();
      } else {
        printf("Callback is not bound.\n");
      }
    }
};

Button::Button() {
  this->callback = new Callback();
}

void Button::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && event->button.x >= this->x && event->button.x <= this->x + this->width && event->button.y >= this->y && event->button.y <= this->y + this->height)
  {
    this->callback->invoke();
  }
}

void Button::render(Window* window) {
  Label::render(window);
  SDL_SetRenderDrawColor(this->getRenderer(window), this->border_Color[0].r, this->border_Color[0].g, this->border_Color[0].b, this->border_Color[0].a);
  SDL_RenderDrawLine(this->getRenderer(window), this->x, this->y, this->x + this->width, this->y);
  SDL_RenderDrawLine(this->getRenderer(window), this->x, this->y, this->x, this->y + this->height);
  SDL_SetRenderDrawColor(this->getRenderer(window), this->border_Color[1].r, this->border_Color[1].g, this->border_Color[1].b, this->border_Color[1].a);
  SDL_RenderDrawLine(this->getRenderer(window), this->x + this->width, this->y, this->x + this->width, this->y + this->height);
  SDL_RenderDrawLine(this->getRenderer(window), this->x, this->y + this->height, this->x + this->width, this->y + this->height);
}

Button::~Button() {
  delete this->callback;
}