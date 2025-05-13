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

class Window;
class Widget {
  protected:
    int x, y, width, height;
    TTF_Font* font;
    std::string id;
    virtual void handleEvent(SDL_Event* event);
    virtual void render(Window* window);
  public:
    Widget(int x, int y, int width, int height);
    Widget();
    void setId(std::string id) { this->id = id; }
    ~Widget();
  friend class Window;
};

class Window {
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Widget*> widgets;
    int width, height, x, y;
    std::string title;
    TTF_Font* font;
    int fontSize = 24;
    SDL_Color background_Color = {0, 0, 0, 255};
    public:
    Window();
    Window(std::string title);
    Window(std::string title, int width, int height);
    Window(std::string title, int width, int height, int x, int y);
    ~Window();
    void mainLoop();
    void update();
    void updateWindow();
    void addWidget(Widget* widget);
    void setFont(TTF_Font* font) { this->font = font; }
    void setTitle(std::string title) { this->title = title; updateWindow(); }
    void setWidth(int width) { this->width = width; updateWindow(); }
    void setHeight(int height) { this->height = height; updateWindow(); }
    void setBackgroundColor(SDL_Color color) { this->background_Color = color; }
    void setFontSize(int fontSize);
    void setX(int x) { this->x = x; updateWindow(); }
    void setY(int y) { this->y = y; updateWindow(); }
    Widget* getWidget(std::string id);
    SDL_Color getBackgroundColor() { return this->background_Color; }
    TTF_Font* getFont() { return this->font; }
    SDL_Renderer* getRednerer() { return this->renderer; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    int getX() { return this->x; }
    int getY() { return this->y; }
    const char* getTitle() { return this->title.c_str(); }
  friend class Widget;
};
#endif

#ifdef __linux__
  #define AQUAUI_PLATFORM "Linux"

#elif _WIN32
  #define AQUAUI_PLATFORM "Windows"

#elif __APPLE__
  #define AQUAUI_PLATFORM "MacOS"

#else
  #define AQUAUI_PLATFORM "Unknown"
#endif

#ifndef AQUAUI_VERSION
  #define AQUAUI_VERSION "0.0.1 pre-alpha"
#endif