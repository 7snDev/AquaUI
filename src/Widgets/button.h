#ifndef AQUAUI_BUTTON_H
#define AQUAUI_BUTTON_H
#include "../core/core.h"
#include "lable.h"
class Window;
class Widget;
class Button : public Widget {
  private:
    Lable *lable;
    std::string text;
    int x = 0, y = 0;
    SDL_Color background_Color = {0, 0, 0, 0};
    SDL_Color text_Color = {255, 255, 255, 255};
    std::function<void()> callback;
  public:
    Button(std::string text);
    ~Button();
    virtual void handleEvent(SDL_Event* event) override;
    void setCallback(std::function<void()> callback) { this->callback = callback; }
    void render(Window* window) override;
    void setPos(int x, int y) { this->x = x; this->y = y; }
    void setColor(SDL_Color color) { this->text_Color = color; }
    void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
    void setText(std::string text) { this->text = text; }
};

#endif