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
  public:
    Window();
    Window(std::string title);
    Window(std::string title, int width, int height);
    Window(std::string title, int width, int height, int x, int y);
    ~Window();
    virtual void mainLoop();
    virtual void update();
    virtual void addWidget(Widget* widget);
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::vector<Widget*> widgets;
    int width, height, x, y;
    std::string title;
};
#endif