#ifndef AQUAUI_TEXTINPUT_H
#define AQUAUI_TEXTINPUT_H

#include "../core/core.h"
#include "Label.h"
class Label;
class Callback;

class TextInput : public Label {
  private:
    std::string placeholder = "text input";
    bool isFocused = false;
    Callback* onChangeCallback = nullptr;
    SDL_Color cursor_Color = {255, 255, 255, 255};
    bool showCursor = true;
    Uint32 lastBlinkTime = 0;
    const Uint32 blinkInterval = 500;
    void render(Window* window) override;
    void handleEvent(SDL_Event* event) override;
  public:
    TextInput() {
      this->text = this->placeholder;
      this->setPadding(10);
      this->setAlignment(Alignment::LEFT);
      for (size_t i = 0; i < 4; i++)
      {
        this->setBorderColor({255, 255, 255, 255}, i);
        this->setBorderWidth(5, i);
      }
      this->setColor({255, 255, 255, 255});
      this->setHoverColor({255, 255, 255, 255});
      this->setBackgroundColor({0, 0, 0, 255});
      this->setHoverBackgroundColor({0, 0, 0, 255});
    };

    void setPlaceholder(std::string placeholder) { this->placeholder = placeholder; }
    void setFocused(bool isFocused) { this->isFocused = isFocused; }
    void setOnChangeCallback(Callback *callback) { this->onChangeCallback = callback; }
    void setCursorColor(SDL_Color color) { this->cursor_Color = color; }

    SDL_Color getCursorColor() { return this->cursor_Color; }
    Callback* getOnChangeCallback() { return this->onChangeCallback; }
    bool getFocused() { return this->isFocused; }
    std::string getPlaceholder() { return this->placeholder; }
  };

#endif