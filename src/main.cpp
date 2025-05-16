
// Manual GUI
// #include <iostream>
// #include "aquaui.h"

// void textChanged(Label* label, TextInput* text_input) {
//   label->setText("Hello, " + text_input->getText());
// }

// int main(int argc, char* argv[]) {
//   Window window;
//   Label label;
//   TextInput text_input;
//   Callback* callback = new Callback();
//   callback->bind(textChanged, &label, &text_input);
//   window.setBackgroundColor({33, 66, 55, 255});

//   label.setText("Hello World!");
//   label.setColor({255, 255, 255, 255});
//   label.setHoverColor({255, 255, 255, 255});
//   window.addWidget(&label);
  
//   text_input.setPlaceholder("Enter your name");
//   text_input.setPos(500, 500);
//   text_input.setOnChangeCallback(callback);
//   window.addWidget(&text_input);

//   window.mainLoop();
//   delete callback;
//   return 0;
// }

// XML GUI (XML Builder)
// #include <iostream>
// #include "aquaui.h"

// int main(int argc, char* argv[]) {
//   Window window;
//   XMLBuilder builder;
//   builder.build(&window, "gui.xml");
//   printf("Completed loading GUI\n");
//   window.mainLoop();
//   return 0;
// }

// XML GUI (XML Compiler)
// #include <iostream>
// #include "aquaui.h"
// #include "gui.h"

// int main(int argc, char* argv[]) {
//   Window window = gui::build();
//   window.mainLoop();
//   return 0;
// }