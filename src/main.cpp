#include <iostream>
#include "aquaui.h"

int count = 0;
Button* button;
void handleClick() {
  count++;
  button->setText(std::to_string(count));
}

int main(int argc, char* argv[]) {
  Window win("AquaUI", 800, 600);
  win.setBackgroundColor({0, 0, 255, 255});

  Lable lable("Lable");
  lable.setPos(100, 100);
  lable.setColor({255, 255, 255, 255});
  win.addWidget(&lable);

  button = new Button("Button");
  button->setPos(500, 200);
  button->setColor({255, 0, 0, 255});
  button->setBackgroundColor({0, 255, 0, 255});
  button->setCallback(&handleClick);
  win.addWidget(button);

  TextInput input("Text Input");
  input.setPos(300, 300);
  input.setColor({255, 255, 255, 255});
  input.setBackgroundColor({0, 0, 0, 255});
  input.setFontSize(24);
  input.setOutline(1, 1, 1, 1);
  win.addWidget(&input);

  win.mainLoop();
  return 0;
}