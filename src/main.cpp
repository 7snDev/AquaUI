#include <iostream>
#include "aquaui.h"

void textChanged(Label* label, TextInput* text_input) {
  label->setText("Hello, " + text_input->getText());
}

int main(int argc, char* argv[]) {
  Window window;
  Label label;
  TextInput text_input;
  Callback* callback = new Callback();
  callback->bind(textChanged, &label, &text_input);
  window.setBackgroundColor({33, 66, 55, 255});

  label.setText("Hello World!");
  label.setColor({255, 255, 255, 255});
  label.setHoverColor({255, 255, 255, 255});
  window.addWidget(&label);
  
  text_input.setPlaceholder("Enter your name");
  text_input.setPos(500, 500);
  text_input.setOnChangeCallback(callback);
  window.addWidget(&text_input);

  window.mainLoop();
  delete callback;
  return 0;
}
