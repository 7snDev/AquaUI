#ifndef AQUAUI_BUTTON_H
#define AQUAUI_BUTTON_H
#include "Label.h"
class Label;

class Button : public Label {
  public:
    Button() {
      for (size_t i = 0; i < 4; i++) {
        this->setBorderWidth(5, i);
        this->setBorderColor({0, 0, 0, 255}, i);
        this->setColor({255, 255, 255, 255});
      }
      this->setPadding(10);
      this->setAlignment(Alignment::CENTER);
      this->setBackgroundColor({0, 0, 0, 255});
      this->setHoverColor({255, 255, 255, 255});
      this->setHoverBackgroundColor({50, 50, 50, 255});
    }
};

#endif