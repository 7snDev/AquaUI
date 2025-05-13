#ifndef AQUAUI_LABLE_H
#define AQUAUI_LABLE_H
#include "../core/core.h"
class Window;
class Widget;
class Lable : public Widget {
  private:
    int x, y = 0;
    std::string text;
    TTF_Font* font = NULL;
    SDL_Color background_Color = {0, 0, 0, 0};
    SDL_Color text_Color = {255, 255, 255, 255};
    int Width = 0, Height = 0;
    public:
    Lable(std::string text) {this->text = text;};
    virtual void render(Window* window) override;
    virtual void handleEvent(SDL_Event* event) override {}
    void setPos(int x, int y) { this->x = x; this->y = y; }
    void setFont(TTF_Font* font) { this->font = font; }
    void setText(std::string text) { this->text = text; }
    void setColor(SDL_Color color) { this->text_Color = color; }
    void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
    int getWidth() { return this->Width; }
    int getHeight() { return this->Height; }
    int getX() { return this->x; }
    int getY() { return this->y; }
    std::string getText() { return this->text; }
};

#endif