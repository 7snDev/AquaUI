#include "XMLBuilder.h"

int safeStoi(const std::string &str)
{
  try {
    return std::stoi(str);
  }
  catch (...)
  {
    throw std::runtime_error("Failed to convert string to integer in XML | " + str);
  }
}


SDL_Color parseColor(const std::string &colorStr)
{
  SDL_Color color;
  std::stringstream ss(colorStr);
  std::string token;
  std::getline(ss, token, ',');
  color.r = safeStoi(token);
  std::getline(ss, token, ',');
  color.g = safeStoi(token);
  std::getline(ss, token, ',');
  color.b = safeStoi(token);
  std::getline(ss, token, ',');
  color.a = safeStoi(token);
  return color;
}

bool checkAttributes(const tinyxml2::XMLElement *element, const char *attributeName)
{
  return element->Attribute(attributeName) != nullptr;
}

void XMLBuilder::build(Window *window, std::string path)
{
  tinyxml2::XMLDocument doc;
  if (doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS)
  {
    printf("Error loading XML file: %s\n", path.c_str());
    return;
  }

  tinyxml2::XMLElement *root = doc.RootElement();
  if (!root)
  {
    printf("No root element found in XML.\n");
    return;
  }

  if (std::string(root->Value()) != "Window")
  {
    printf("Root element is not 'Window' | the root element is '%s'", root->Value());
    return;
  }

  if (std::string(root->Attribute("version")) != AQUAUI_VERSION)
  {
    printf("Root element attribute 'version' is not '%s'.", AQUAUI_VERSION);
    return;
  }

  if (!root->Attribute("background_color") ||
      !root->Attribute("width") ||
      !root->Attribute("height") ||
      !root->Attribute("x") ||
      !root->Attribute("y") ||
      !root->Attribute("fontSize") ||
      !root->Attribute("title") ||
      !root->Attribute("fullscreen") ||
      !root->Attribute("resizable") ||
      !root->Attribute("icon"))
  {
    printf("Missing attributes in Window element - ");
    if (!root->Attribute("background_color")) printf("background_color\n");
    if (!root->Attribute("width")) printf("width\n");
    if (!root->Attribute("height")) printf("height\n");
    if (!root->Attribute("x")) printf("x\n");
    if (!root->Attribute("y")) printf("y\n");
    if (!root->Attribute("fontSize")) printf("fontSize\n");
    if (!root->Attribute("title")) printf("title\n");
    if (!root->Attribute("fullscreen")) printf("fullscreen\n");
    if (!root->Attribute("resizable")) printf("resizable\n");
    if (!root->Attribute("icon")) printf("icon\n");
    return;
  }

  window->setBackgroundColor(parseColor(std::string(root->Attribute("background_color"))));
  window->setWidth(safeStoi(std::string(root->Attribute("width"))));
  window->setHeight(safeStoi(std::string(root->Attribute("height"))));
  window->setX(safeStoi(std::string(root->Attribute("x"))));
  window->setY(safeStoi(std::string(root->Attribute("y"))));
  window->setFontSize(safeStoi(std::string(root->Attribute("fontSize"))));
  window->setTitle(std::string(root->Attribute("title")));
  window->setFullscreen(safeStoi(std::string(root->Attribute("fullscreen"))));
  window->setResizable(safeStoi(std::string(root->Attribute("resizable"))));
  window->setIcon(std::string(root->Attribute("icon")));

  for (auto child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    std::string type = std::string(child->Value());

    if (type == "Label")
    {
      Label *label = new Label();
      if (checkAttributes(child, "text") &&
          checkAttributes(child, "color") &&
          checkAttributes(child, "background_color") &&
          checkAttributes(child, "padding") &&
          checkAttributes(child, "alignment") &&
          checkAttributes(child, "hover_color") &&
          checkAttributes(child, "hover_background_color") &&
          checkAttributes(child, "id") &&
          checkAttributes(child, "x") &&
          checkAttributes(child, "y") &&
          checkAttributes(child, "z_index") &&
          checkAttributes(child, "width") &&
          checkAttributes(child, "height"))
      {
        label->setGeometry(safeStoi(std::string(child->Attribute("x"))),
                           safeStoi(std::string(child->Attribute("y"))),
                           safeStoi(std::string(child->Attribute("width"))),
                           safeStoi(std::string(child->Attribute("height"))));
        label->setText(std::string(child->Attribute("text")));
        label->setColor(parseColor(std::string(child->Attribute("color"))));
        label->setBackgroundColor(parseColor(std::string(child->Attribute("background_color"))));
        label->setPadding(safeStoi(std::string(child->Attribute("padding"))));
        label->setAlignment((Alignment)safeStoi(std::string(child->Attribute("alignment"))));
        label->setHoverColor(parseColor(std::string(child->Attribute("hover_color"))));
        label->setHoverBackgroundColor(parseColor(std::string(child->Attribute("hover_background_color"))));
        label->setId(std::string(child->Attribute("id")));
        window->addWidget(label);
      } else {
        printf("Missing attributes in Label element - ");
        if (!child->Attribute("text")) printf("text\n");
        if (!child->Attribute("color")) printf("color\n");
        if (!child->Attribute("background_color")) printf("background_color\n");
        if (!child->Attribute("padding")) printf("padding\n");
        if (!child->Attribute("alignment")) printf("alignment\n");
        if (!child->Attribute("hover_color")) printf("hover_color\n");
        if (!child->Attribute("hover_background_color")) printf("hover_background_color\n");
        if (!child->Attribute("id")) printf("id\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("z_index")) printf("z_index\n");
        if (!child->Attribute("width")) printf("width\n");
        if (!child->Attribute("height")) printf("height\n");
        return;
      }
    } else if (type == "Button")
    {
      Button *button = new Button();
      if (checkAttributes(child, "text") &&
          checkAttributes(child, "color") &&
          checkAttributes(child, "background_color") &&
          checkAttributes(child, "padding") &&
          checkAttributes(child, "alignment") &&
          checkAttributes(child, "hover_color") &&
          checkAttributes(child, "hover_background_color") &&
          checkAttributes(child, "id") &&
          checkAttributes(child, "x") &&
          checkAttributes(child, "y") &&
          checkAttributes(child, "z_index") &&
          checkAttributes(child, "width") &&
          checkAttributes(child, "height"))
      {
        button->setGeometry(safeStoi(std::string(child->Attribute("x"))),
                            safeStoi(std::string(child->Attribute("y"))),
                            safeStoi(std::string(child->Attribute("width"))),
                            safeStoi(std::string(child->Attribute("height"))));
        button->setText(std::string(child->Attribute("text")));
        button->setColor(parseColor(std::string(child->Attribute("color"))));
        button->setBackgroundColor(parseColor(std::string(child->Attribute("background_color"))));
        button->setPadding(safeStoi(std::string(child->Attribute("padding"))));
        button->setAlignment((Alignment)safeStoi(std::string(child->Attribute("alignment"))));
        button->setHoverColor(parseColor(std::string(child->Attribute("hover_color"))));
        button->setHoverBackgroundColor(parseColor(std::string(child->Attribute("hover_background_color"))));
        button->setId(std::string(child->Attribute("id")));
        window->addWidget(button);
      } else {
        printf("Missing attributes in Button element - ");
        if (!child->Attribute("text")) printf("text\n");
        if (!child->Attribute("color")) printf("color\n");
        if (!child->Attribute("background_color")) printf("background_color\n");
        if (!child->Attribute("padding")) printf("padding\n");
        if (!child->Attribute("alignment")) printf("alignment\n");
        if (!child->Attribute("hover_color")) printf("hover_color\n");
        if (!child->Attribute("hover_background_color")) printf("hover_background_color\n");
        if (!child->Attribute("id")) printf("id\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("z_index")) printf("z_index\n");
        if (!child->Attribute("width")) printf("width\n");
        if (!child->Attribute("height")) printf("height\n");
        return;
      }
    } else if (type == "TextInput")
    {
      TextInput *textInput = new TextInput();
      if (checkAttributes(child, "placeholder") &&
          checkAttributes(child, "color") &&
          checkAttributes(child, "background_color") &&
          checkAttributes(child, "padding") &&
          checkAttributes(child, "alignment") &&
          checkAttributes(child, "hover_color") &&
          checkAttributes(child, "hover_background_color") &&
          checkAttributes(child, "id") &&
          checkAttributes(child, "x") &&
          checkAttributes(child, "y") &&
          checkAttributes(child, "width") &&
          checkAttributes(child, "height") &&
          checkAttributes(child, "z_index") &&
          checkAttributes(child, "cursor_color"))
      {
        textInput->setGeometry(safeStoi(std::string(child->Attribute("x"))),
                               safeStoi(std::string(child->Attribute("y"))),
                               safeStoi(std::string(child->Attribute("width"))),
                               safeStoi(std::string(child->Attribute("height"))));
        textInput->setPlaceholder(std::string(child->Attribute("placeholder")));
        textInput->setColor(parseColor(std::string(child->Attribute("color"))));
        textInput->setBackgroundColor(parseColor(std::string(child->Attribute("background_color"))));
        textInput->setPadding(safeStoi(std::string(child->Attribute("padding"))));
        textInput->setAlignment((Alignment)safeStoi(std::string(child->Attribute("alignment"))));
        textInput->setHoverColor(parseColor(std::string(child->Attribute("hover_color"))));
        textInput->setHoverBackgroundColor(parseColor(std::string(child->Attribute("hover_background_color"))));
        textInput->setId(std::string(child->Attribute("id")));
        textInput->setCursorColor(parseColor(std::string(child->Attribute("cursor_color"))));
        textInput->setZIndex(safeStoi(std::string(child->Attribute("z_index"))));
        window->addWidget(textInput);
      } else {
        printf("Missing attributes in TextInput element - ");
        if (!child->Attribute("placeholder")) printf("placeholder\n");
        if (!child->Attribute("color")) printf("color\n");
        if (!child->Attribute("z_index")) printf("z_index\n");
        if (!child->Attribute("background_color")) printf("background_color\n");
        if (!child->Attribute("padding")) printf("padding\n");
        if (!child->Attribute("alignment")) printf("alignment\n");
        if (!child->Attribute("hover_color")) printf("hover_color\n");
        if (!child->Attribute("hover_background_color")) printf("hover_background_color\n");
        if (!child->Attribute("id")) printf("id\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("width")) printf("width\n");
        if (!child->Attribute("height")) printf("height\n");
        if (!child->Attribute("cursor_color")) printf("cursor_color\n");
        return;
      }
    } else if (type == "Frame")
    {
      Frame *frame = new Frame();
      if (checkAttributes(child, "src") &&
          checkAttributes(child, "id") &&
          checkAttributes(child, "x") &&
          checkAttributes(child, "z_index") &&
          checkAttributes(child, "y") &&
          checkAttributes(child, "width") &&
          checkAttributes(child, "height"))
      {
        frame->setSrc(std::string(child->Attribute("src")));
        frame->setId(std::string(child->Attribute("id")));
        frame->setGeometry(safeStoi(std::string(child->Attribute("x"))),
                           safeStoi(std::string(child->Attribute("y"))),
                           safeStoi(std::string(child->Attribute("width"))),
                           safeStoi(std::string(child->Attribute("height"))));
        frame->setZIndex(safeStoi(std::string(child->Attribute("z_index"))));
        window->addWidget(frame);
      } else {
        printf("Missing attributes in Frame element - ");
        if (!child->Attribute("src")) printf("src\n");
        if (!child->Attribute("id")) printf("id\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("z_index")) printf("z_index\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("width")) printf("width\n");
        if (!child->Attribute("height")) printf("height\n");
        return;
      }
    }
  }
}