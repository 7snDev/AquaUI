#ifndef AQUAUI_BUTTON_H
#define AQUAUI_BUTTON_H
#include "../core/core.h"
#include "Label.h"
class Window;
class Widget;
class Label;
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

class Button : public Label {
  private:
    Callback* callback;
    SDL_Color press_Color;
    SDL_Color border_Color[4] = { {255, 255, 255, 255}, {255, 255, 255, 255}, {255, 255, 255, 255}, {255, 255, 255, 255} };
    int border_Width[4] = { 5, 5, 5, 5 };

    void handleEvent(SDL_Event* event) override;
    void render(Window* _window) override;
  public:
    Button();
    ~Button();
    void setPressColor(SDL_Color color) { this->press_Color = color; }
    void setBorderColor(SDL_Color color, int index) { this->border_Color[index] = color; }
    void setBorderWidth(int width, int index) { this->border_Width[index] = width * -1; }
    void setCallback(Callback* callback) { this->callback = callback; }
    
    int getBorderWidth(int index) { return this->border_Width[index]; }
    SDL_Color getPressColor() { return this->press_Color; }
    SDL_Color getBorderColor(int index) { return this->border_Color[index]; }
    Callback* getCallback() { return this->callback; }
  };
  
  #endif