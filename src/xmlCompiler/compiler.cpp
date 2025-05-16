#define AQUAUI_VERSION "1.0.0-Beta"

#include <tinyxml2.h>
#include <fstream>
#include <iostream>
using namespace std;
using namespace tinyxml2;

string readFile(string path) {
  string content;
  ifstream file(path);
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      content += line + "\n";
    }
    file.close();
  }
  return content;
}

bool checkAttributes(const tinyxml2::XMLElement *element, const char *attributeName) {
  return element->Attribute(attributeName) != nullptr;
}

string toAlignment(string alignment) {
  if (alignment == "0") return "LEFT";
  if (alignment == "1") return "CENTER";
  if (alignment == "2") return "RIGHT";
  return "LEFT";
}

string generateUI(string content) {
  string ui = "#include\"gui.h\"\nWindow gui::build(){";
  int widgets[4] = {0, 0, 0, 0};
  tinyxml2::XMLDocument doc;
  if (doc.Parse(content.c_str()) != tinyxml2::XML_SUCCESS)
  {
    printf("Error loading XML file: %s\n", content.c_str());
    return "";
  }

  tinyxml2::XMLElement *root = doc.RootElement();
  if (!root)
  {
    printf("No root element found in XML.\n");
    return "";
  }

  if (std::string(root->Value()) != "Window")
  {
    printf("Root element is not 'Window' | the root element is '%s'", root->Value());
    return "";
  }

  if (std::string(root->Attribute("version")) != AQUAUI_VERSION)
  {
    printf("Root element attribute 'version' is not '%s'.", AQUAUI_VERSION);
    return "";
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
    return "";
  }

  ui.append("Window w;w.setBackgroundColor({" + std::string(root->Attribute("background_color")) + "});" +
            "w.setWidth(" + std::string(root->Attribute("width")) + ");" +
            "w.setHeight(" + std::string(root->Attribute("height")) + ");" +
            "w.setX(" + std::string(root->Attribute("x")) + ");" +
            "w.setY(" + std::string(root->Attribute("y")) + ");" +
            "w.setFontSize(" + std::string(root->Attribute("fontSize")) + ");" +
            "w.setTitle(\"" + std::string(root->Attribute("title")) + "\");" +
            "w.setFullscreen(" + std::string(root->Attribute("fullscreen")) + ");" +
            "w.setResizable(" + std::string(root->Attribute("resizable")) + ");");
  for (auto child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    std::string type = std::string(child->Value());
    if (type == "Label")
    {
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
        widgets[0]++;
        string id = "l" + std::to_string(widgets[0]);
        ui.append("Label " + id + ";" + id + ".setText(\"" + std::string(child->Attribute("text")) + "\");" +
                  id + ".setColor({" + std::string(child->Attribute("color")) + "});" +
                  id + ".setBackgroundColor({" + std::string(child->Attribute("background_color")) + "});" +
                  id + ".setPadding(" + std::string(child->Attribute("padding")) + ");" +
                  id + ".setAlignment(" + toAlignment(std::string(child->Attribute("alignment"))) + ");" +
                  id + ".setHoverColor({" + std::string(child->Attribute("hover_color")) + "});" +
                  id + ".setHoverBackgroundColor({" + std::string(child->Attribute("hover_background_color")) + "});" +
                  id + ".setId(\"" + std::string(child->Attribute("id")) + "\");" +
                  id + ".setX(" + std::string(child->Attribute("x")) + ");" +
                  id + ".setY(" + std::string(child->Attribute("y")) + ");" +
                  id + ".setZIndex(" + std::string(child->Attribute("z_index")) + ");" +
                  id + ".setWidth(" + std::string(child->Attribute("width")) + ");" +
                  id + ".setHeight(" + std::string(child->Attribute("height")) + ");");
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
        return "Error in Label element";
      }
    } else if (type == "Button")
    {
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
        widgets[1]++;
        string id = "b" + std::to_string(widgets[1]);
        ui.append("Button " + id + ";" + id + ".setText(\"" + std::string(child->Attribute("text")) + "\");" +
                  id + ".setColor({" + std::string(child->Attribute("color")) + "});" +
                  id + ".setBackgroundColor({" + std::string(child->Attribute("background_color")) + "});" +
                  id + ".setPadding(" + std::string(child->Attribute("padding")) + ");" +
                  id + ".setAlignment(" + toAlignment(std::string(child->Attribute("alignment"))) + ");" +
                  id + ".setHoverColor({" + std::string(child->Attribute("hover_color")) + "});" +
                  id + ".setHoverBackgroundColor({" + std::string(child->Attribute("hover_background_color")) + "});" +
                  id + ".setId(\"" + std::string(child->Attribute("id")) + "\");" +
                  id + ".setX(" + std::string(child->Attribute("x")) + ");" +
                  id + ".setY(" + std::string(child->Attribute("y")) + ");" +
                  id + ".setZIndex(" + std::string(child->Attribute("z_index")) + ");" +
                  id + ".setWidth(" + std::string(child->Attribute("width")) + ");" +
                  id + ".setHeight(" + std::string(child->Attribute("height")) + ");");
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
        return "Error in Button element";
      }
    } else if (type == "TextInput")
    {
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
        widgets[2]++;
        string id = "t" + std::to_string(widgets[2]);
        ui.append("TextInput " + id + ";" + id + ".setPlaceholder(\"" + std::string(child->Attribute("placeholder")) + "\");" +
                  id + ".setColor({" + std::string(child->Attribute("color")) + "});" +
                  id + ".setBackgroundColor({" + std::string(child->Attribute("background_color")) + "});" +
                  id + ".setPadding(" + std::string(child->Attribute("padding")) + ");" +
                  id + ".setAlignment(" + toAlignment(std::string(child->Attribute("alignment"))) + ");" +
                  id + ".setHoverColor({" + std::string(child->Attribute("hover_color")) + "});" +
                  id + ".setHoverBackgroundColor({" + std::string(child->Attribute("hover_background_color")) + "});" +
                  id + ".setId(\"" + std::string(child->Attribute("id")) + "\");" +
                  id + ".setX(" + std::string(child->Attribute("x")) + ");" +
                  id + ".setY(" + std::string(child->Attribute("y")) + ");" +
                  id + ".setZIndex(" + std::string(child->Attribute("z_index")) + ");" +
                  id + ".setWidth(" + std::string(child->Attribute("width")) + ");" +
                  id + ".setHeight(" + std::string(child->Attribute("height")) + ");" +
                  id + ".setCursorColor({" + std::string(child->Attribute("cursor_color")) + "});");
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
        return "Error in TextInput element";
      }
    } else if (type == "Frame")
    {
      if (checkAttributes(child, "src") &&
          checkAttributes(child, "id") &&
          checkAttributes(child, "x") &&
          checkAttributes(child, "z_index") &&
          checkAttributes(child, "y") &&
          checkAttributes(child, "width") &&
          checkAttributes(child, "height"))
      {
        widgets[3]++;
        string id = "f" + std::to_string(widgets[3]);
        ui.append("Frame " + id + ";" + id + ".setSrc(\"" + std::string(child->Attribute("src")) + "\");" +
                  id + ".setId(\"" + std::string(child->Attribute("id")) + "\");" +
                  id + ".setX(" + std::string(child->Attribute("x")) + ");" +
                  id + ".setZIndex(" + std::string(child->Attribute("z_index")) + ");" +
                  id + ".setY(" + std::string(child->Attribute("y")) + ");" +
                  id + ".setWidth(" + std::string(child->Attribute("width")) + ");" +
                  id + ".setHeight(" + std::string(child->Attribute("height")) + ");");
      } else {
        printf("Missing attributes in Frame element - ");
        if (!child->Attribute("src")) printf("src\n");
        if (!child->Attribute("id")) printf("id\n");
        if (!child->Attribute("x")) printf("x\n");
        if (!child->Attribute("z_index")) printf("z_index\n");
        if (!child->Attribute("y")) printf("y\n");
        if (!child->Attribute("width")) printf("width\n");
        if (!child->Attribute("height")) printf("height\n");
        return "Error in Frame element";
      }
    }
  }
  ui.append("return w;}");
  return ui;
}

string generateHeader() {
  string header;
  header.append("#include\"aquaui.h\"\nnamespace gui{Window build();};");
  return header;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }
  string path = argv[1];
  string content = readFile(path);
  string ui_generated_path = path.substr(0, path.find_last_of(".")) + ".cpp";
  ofstream ui_generated(ui_generated_path);
  ui_generated << generateUI(content);
  ui_generated.close();
  ofstream header(path.substr(0, path.find_last_of(".")) + ".h");
  header << generateHeader();
  header.close();
  return 0;
}