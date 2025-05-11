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


class Widget {
  private:
    int x, y, width, height;
    virtual void handleEvent(SDL_Event* event);
    virtual void render(SDL_Renderer* renderer);
  public:
    Widget(int x, int y, int width, int height);
    Widget();

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
    public:
    Window();
    Window(std::string title);
    Window(std::string title, int width, int height);
    Window(std::string title, int width, int height, int x, int y);
    ~Window();
    virtual void mainLoop();
    virtual void update();
    virtual void addWidget(Widget* widget);
    void setFont(TTF_Font* font) { this->font = font; }
    void setTitle(std::string title) { this->title = title; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    TTF_Font* getFont() { return this->font; }
    void setFontSize(int fontSize);
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