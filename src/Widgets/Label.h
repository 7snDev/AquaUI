#ifndef AQUAUI_LABLE_H
#define AQUAUI_LABLE_H
#include "../core/core.h"
class Window;
class Widget;

enum Alignment {
  LEFT,
  RIGHT,
  CENTER
};

class Label : public Widget {
  private:
    std::string text;
    SDL_Color text_Color = {0, 0, 0, 255};
    SDL_Color background_Color = {0, 0, 0, 0};
    int padding = 0;
    Alignment alignment = Alignment::LEFT;

  protected:
    void render(Window* window) override;

    public:
    void setText(std::string text) { this->text = text; }
    void setColor(SDL_Color color) { this->text_Color = color; }
    void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
    void setPadding(int padding);
    void setAlignment(Alignment alignment) { this->alignment = alignment; }

    std::string getText() { return this->text; }
    SDL_Color getColor() { return this->text_Color; }
    SDL_Color getBackgroundColor() { return this->background_Color; }
    int getPadding() { return this->padding; }
    Alignment getAlignment() { return this->alignment; }
};

#endif