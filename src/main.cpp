#include <iostream>
#include "aquaui.h"

void handlePress(Label* label) {
  if (label->getText() == "Hello World!")
    label->setText("Goodbye World!");
  else 
    label->setText("Hello World!");
}

int main(int argc, char* argv[]) {
  Window window;
  Label label;
  Button button;
  Callback* callback = new Callback();
  window.setBackgroundColor({33, 66, 55, 255});

  label.setText("Hello World!");
  label.setColor({255, 255, 255, 255});
  window.addWidget(&label);
  
  callback->bind(handlePress, &label);
  button.setText("Press");
  button.setCallback(callback);
  button.setPressColor({255, 0, 0, 255});
  button.setPadding(10);
  button.setAlignment(Alignment::CENTER);
  for (int i = 0; i < 4; i++) {
    button.setBorderColor({255, 255, 255, 255}, i);
    button.setBorderWidth(5, i);
  }
  button.setColor({255, 255, 255, 255});
  button.setPos(50, 50);
  button.setBackgroundColor({0, 0, 0, 255});
  window.addWidget(&button);
  
  window.mainLoop();
  return 0;
}