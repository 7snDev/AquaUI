#include <iostream>
#include "core.h"
#include "Widgets/lable.h"
int main(int argc, char* argv[]) {
  try {
    Window win("AquaUI", 800, 600);
    TTF_Font* font = TTF_OpenFont("Arial.otf", 50);
    Lable lable("Hello", 10, 10, {255, 255, 255}, {0, 0, 0}, font);
    win.addWidget(&lable);
    win.mainLoop();
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
    return 1;
  }
  return 0;
}