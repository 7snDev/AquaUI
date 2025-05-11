#ifndef AQUAUI_LABLE_H
#define AQUAUI_LABLE_H

#include "../core/core.h"

class Lable : public Widget {
  private:
    int x, y;
    std::string text;
    SDL_Color background_Color;
    SDL_Color text_Color;
    TTF_Font* font;
  public:
    Lable(std::string text, int x, int y, SDL_Color text_Color, SDL_Color background_Color, TTF_Font* font);
    virtual void render(SDL_Renderer* renderer) override;
    virtual void handleEvent(SDL_Event* event) override {}
    void setText(std::string text) { this->text = text; }
};

#endif