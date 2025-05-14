#ifndef AQUAUI_CORE_H
#define AQUAUI_CORE_H
  #include <string>
  #include <cstdio>
  #include <vector>
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_image.h>
  #include <SDL2/SDL_mixer.h>
  #include <stdexcept>
  #include <filesystem>
  #include <functional>
  #include <unordered_map>
  #include <vector>
  #include <tuple>
  #include <utility>

class Widget;
class Window {
  private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  std::vector<Widget*> widgets;
  SDL_Color background_Color = {0, 0, 0, 255};
  int width = 800, height = 600, x = 100, y = 100;
  TTF_Font* font = nullptr;
  int fontSize = 24;
  std::string title = "AquaUI";
  SDL_Surface *icon = nullptr;
  bool fullscreen = false;
  bool resizable = true;
  
  void update();
  void updateWindow();
  void handleEvent(SDL_Event* event);

  protected:
  SDL_Renderer* getRenderer() { return this->renderer; }
  
  public:
  Window();
  ~Window();
  void setGeometry(int x, int y, int width, int height) { this->x = x; this->y = y; this->width = width; this->height = height; }
  void setPos(int x, int y) { this->x = x; this->y = y; }
  void setWidth(int width) { this->width = width; }
  void setHeight(int height) { this->height = height; }
  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
  void setTitle(std::string title) { this->title = title; }
  void setFont(TTF_Font* font) { this->font = font; }
  void setFontSize(int fontSize);
  void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
  void addWidget(Widget* widget) { this->widgets.push_back(widget); }
  
  Widget* getWidget(std::string id);
  int getWidth() { return this->width; }
  int getHeight() { return this->height; }
  int getX() { return this->x; }
  int getY() { return this->y; }
  std::string getTitle() { return this->title; }
  TTF_Font* getFont() { return this->font; }
  int getFontSize() { return this->fontSize; }
  SDL_Color getBackgroundColor() { return this->background_Color; }
  
  void mainLoop();
  friend class Widget;
};

class Widget {
  protected:
  std::string id; 
  int x = 0, y = 0, width = 0, height = 0;
  TTF_Font* font = nullptr;
  virtual void handleEvent(SDL_Event* event);
  virtual void render(Window* window);
  SDL_Renderer* getRenderer(Window* window) { return window->getRenderer(); }
  public:
  void setGeometry(int x, int y, int width, int height) { this->x = x; this->y = y; this->width = width; this->height = height; }
  void setPos(int x, int y) { this->x = x; this->y = y; }
  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    void setId(std::string id) { this->id = id; }
    void setFont(TTF_Font* font) { this->font = font; }
    
    int getX() { return this->x; }
    int getY() { return this->y; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    std::string getId() { return this->id; }
    TTF_Font* getFont() { return this->font; }
    friend class Window;
};
#endif

#ifndef AQUAUI_VERSION
  #define AQUAUI_VERSION "0.0.1 pre-alpha"
#endif

#ifdef __linux__
  #define AQUAUI_PLATFORM "Linux"
#elif _WIN32 || __WIN32__ || _WIN64 || __WIN64__
  #define AQUAUI_PLATFORM "Windows"
#else
  #define AQUAUI_PLATFORM "Not Supported Platform"
#endif