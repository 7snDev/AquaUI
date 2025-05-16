#ifndef AQUAUI_XMLBUILDER_H
#define AQUAUI_XMLBUILDER_H

#include <tinyxml2.h>
#include "core.h"
#include "../Widgets/Label.h"
#include "../Widgets/Button.h"
#include "../Widgets/Frame.h"
#include "../Widgets/TextInput.h"

class XMLBuilder {
  public:
    static void build(Window* window, std::string path);
};
#endif