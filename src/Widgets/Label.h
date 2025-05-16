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
  protected:
    std::string text;
    bool isHovered = false;
    SDL_Color border_Color[4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
    int border_Width[4] = { 5, 5, 5, 5 };
    SDL_Color text_Color = {0, 0, 0, 255};
    SDL_Color Hover_Color = {0, 0, 0, 255};
    SDL_Color background_Color = {0, 0, 0, 0};
    SDL_Color Hover_Background_Color = {0, 0, 0, 0};
    int padding = 0;
    Alignment alignment = Alignment::LEFT;

    void handleEvent(SDL_Event* event) override;
    void render(Window* window) override;

    public:
    void setText(std::string text) { this->text = (text != "") ? text : " "; }
    void setColor(SDL_Color color) { this->text_Color = color; }
    void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
    void setPadding(int padding);
    void setAlignment(Alignment alignment) { this->alignment = alignment; }
    void setBorderColor(SDL_Color color, int index) { this->border_Color[index] = color; }
    void setBorderWidth(int width, int index) { this->border_Width[index] = width * -1; }
    void setHoverColor(SDL_Color color) { this->Hover_Color = color; }
    void setHoverBackgroundColor(SDL_Color color) { this->Hover_Background_Color = color; }

    SDL_Color getHoverColor() { return this->Hover_Color; }
    SDL_Color getHoverBackgroundColor() { return this->Hover_Background_Color; }
    int getBorderWidth(int index) { return this->border_Width[index]; }
    SDL_Color getBorderColor(int index) { return this->border_Color[index]; }
    std::string getText() {
      if (this->text.at(0) == ' ')
        return this->text.substr(1);
      else
        return this->text;
    }
    SDL_Color getColor() { return this->text_Color; }
    SDL_Color getBackgroundColor() { return this->background_Color; }
    int getPadding() { return this->padding; }
    Alignment getAlignment() { return this->alignment; }
};

#endif