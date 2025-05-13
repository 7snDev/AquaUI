#include "xmlBuilder.h"

SDL_Color parseColor(const std::string &colorStr)
{
  SDL_Color color;

  std::stringstream ss(colorStr);
  std::string token;
  std::getline(ss, token, ',');
  color.r = std::stoi(token);
  std::getline(ss, token, ',');
  color.g = std::stoi(token);
  std::getline(ss, token, ',');
  color.b = std::stoi(token);
  std::getline(ss, token, ',');
  color.a = std::stoi(token);
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

  if (!root->Attribute("title") || !root->Attribute("width") || !root->Attribute("height") || !root->Attribute("x") || !root->Attribute("y") || !root->Attribute("backgroundColor"))
  {
    printf("Missing attributes in root element - ");
    if (!root->Attribute("title")) printf("title\n");
    if (!root->Attribute("width")) printf("width\n");
    if (!root->Attribute("height")) printf("height\n");
    if (!root->Attribute("x")) printf("x\n");
    if (!root->Attribute("y")) printf("y\n");
    if (!root->Attribute("backgroundColor")) printf("backgroundColor\n");
    return;
  }
  window->setTitle(std::string(root->Attribute("title")));
  window->setWidth(std::stoi(root->Attribute("width")));
  window->setHeight(std::stoi(std::string(root->Attribute("height"))));
  window->setX(std::stoi(root->Attribute("x")));
  window->setY(std::stoi(root->Attribute("y")));
  window->setBackgroundColor(parseColor(std::string(root->Attribute("backgroundColor"))));
  for (auto child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    std::string type = std::string(child->Value());

    if (type == "Button")
    {
      Button *button = new Button(std::string(child->Attribute("text")));
      if (checkAttributes(child, "text") && checkAttributes(child, "id") && checkAttributes(child, "x") && checkAttributes(child, "y") && checkAttributes(child, "color") && checkAttributes(child, "backgroundColor"))
      {
        button->setText(std::string(child->Attribute("text")));
        button->setPos(std::stoi(child->Attribute("x")), std::stoi(child->Attribute("y")));
        button->setColor(parseColor(std::string(child->Attribute("color"))));
        button->setBackgroundColor(parseColor(std::string(child->Attribute("backgroundColor"))));
        button->setId(std::string(child->Attribute("id")));
        window->addWidget(button);
      } else {
        printf("Missing attributes in Button element - ");
        if (!child->Attribute("text")) printf("text\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("color")) printf("color\n");
        if (!child->Attribute("backgroundColor")) printf("backgroundColor\n");
        return;
      }
    } else if (type == "Lable")
    {
      if (checkAttributes(child, "text") && checkAttributes(child, "id") && checkAttributes(child, "x") && checkAttributes(child, "y") && checkAttributes(child, "color") && checkAttributes(child, "backgroundColor"))
      {
        Lable *lable = new Lable(std::string(child->Attribute("text")));
        lable->setPos(std::stoi(child->Attribute("x")), std::stoi(child->Attribute("y")));
        lable->setColor(parseColor(std::string(child->Attribute("color"))));
        lable->setBackgroundColor(parseColor(std::string(child->Attribute("backgroundColor"))));
        lable->setId(std::string(child->Attribute("id")));
        window->addWidget(lable);
      } else {
        printf("Missing attributes in Lable element - ");
        if (!child->Attribute("text")) printf("text\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("color")) printf("color\n");
        if (!child->Attribute("backgroundColor")) printf("backgroundColor\n");
        return;
      }
    } else {
      printf("Unknown element type: %s\n", type.c_str());
      return;
    }
  }
}