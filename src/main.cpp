#include <iostream>
#include "core/core.h"
#include "Widgets/lable.h"

int main(int argc, char* argv[]) {
  printf("Platform: %s\n", AQUAUI_PLATFORM);
  Window win("AquaUI", 800, 600);
  Lable lable("Hello", 10, 10, {255, 255, 255}, {0, 0, 0}, win.getFont());
  win.addWidget(&lable);
  win.mainLoop();

  return 0;
}