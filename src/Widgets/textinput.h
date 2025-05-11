#ifndef AQUAUI_TEXTINPUT_H
#define AQUAUI_TEXTINPUT_H

#include "../core/core.h"
#include "lable.h"
class Window;
class Widget;
class Lable;

class TextInput : public Widget {
  private:
    Lable *lable;
    std::string placeholder;
    SDL_Color color = {255, 255, 255, 255};
    SDL_Color background_Color = {0, 0, 0, 0};
    int fontSize = 24;
    bool focused = false;
    SDL_Color cursor_Color = {255, 255, 255, 255};
    int outline[2][2] = {
      {0, 0},
      {0, 0}};
    TTF_Font* font = NULL;
  public:
    TextInput(std::string placeholder) { this->placeholder = placeholder; this->lable = new Lable(placeholder); };
    ~TextInput();
    virtual void handleEvent(SDL_Event* event) override;
    void render(Window* window) override;
    void setPlaceholder(std::string placeholder) { this->placeholder = placeholder; }
    void setColor(SDL_Color color) { this->color = color; }
    void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
    void setFontSize(int fontSize) { this->fontSize = fontSize; }
    void setCursorColor(SDL_Color color) { this->cursor_Color = color; }
    void setOutline(int x1, int y1, int x2, int y2) { this->outline[0][0] = x1; this->outline[0][1] = y1; this->outline[1][0] = x2; this->outline[1][1] = y2; }
    void setFocused(bool focused) { this->focused = focused; }
    void setPos(int x, int y) { this->x = x; this->y = y; }
    std::string getText() { return this->placeholder; }
};

#endif