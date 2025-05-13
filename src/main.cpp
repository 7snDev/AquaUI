#include "aquaui.h"
#include <iostream>

void handleClick() {
  std::cout << "Clicked" << std::endl;
}

int main(int argc, char* argv[]) {
  XMLBuilder builder;
  Window window("AquaUI");
  builder.build(&window, "xmlTest.xml");

  Button* button = (Button*)window.getWidget("button1");
  if (button == nullptr)
  {
    std::cout << "Button not found" << std::endl;
    return 1;
  }
  button->setCallback(handleClick);
  
  window.mainLoop();
  delete button;
  return 0;
}