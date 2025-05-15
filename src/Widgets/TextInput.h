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

    Callback* getOnChangeCallback() { return this->onChangeCallback; }
    bool getFocused() { return this->isFocused; }
    std::string getPlaceholder() { return this->placeholder; }
  };

#endif