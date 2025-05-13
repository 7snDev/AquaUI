#ifndef AQUAUI_XML_BUILDER_H
#define AQUAUI_XML_BUILDER_H
  #include "core.h"
  #include "../Widgets/lable.h"
  #include "../Widgets/button.h"
  #include "../Widgets/textinput.h"
  #include <tinyxml2.h>

class XMLBuilder {
  public:
    static void build(Window* window, std::string path);
};
#endif