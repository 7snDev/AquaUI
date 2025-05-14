#ifndef AQUAUI_BUTTON_H
#define AQUAUI_BUTTON_H
#include "../core/core.h"
#include "Label.h"
class Window;
class Widget;
class Label;
class Callback;

class Button : public Label {
  private:
    Callback* callback;
    SDL_Color press_Color;
    SDL_Color border_Color[2] = { {255, 255, 255, 255}, {255, 255, 255, 255} };
    int border_Width[2] = { 3, 3 };

    void handleEvent(SDL_Event* event) override;
    void render(Window* _window) override;
  public:
    Button();
    ~Button();
    void setCallback(Callback* callback) { this->callback = callback; }
    void setPressColor(SDL_Color color) { this->press_Color = color; }
    void setBorderColor(SDL_Color color, int index) { this->border_Color[index] = color; }
    void setBorderWidth(int width, int index) { this->border_Width[index] = width; }

    int getBorderWidth(int index) { return this->border_Width[index]; }
    SDL_Color getPressColor() { return this->press_Color; }
    SDL_Color getBorderColor(int index) { return this->border_Color[index]; }
    Callback* getCallback() { return this->callback; }
};

#endif