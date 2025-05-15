#ifndef AQUAUI_FRAME_H
#define AQUAUI_FRAME_H

#include "../core/core.h"

class Window;
class Widget;

class Frame : public Widget {
  private:
    std::string src = "";
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Rect rect = {0, 0, 0, 0};

    void render(Window* window) override;
    void handleEvent(SDL_Event* event) override;
  public:
    ~Frame();
    void setSrc(std::string src);
    void setAutoSize();

    std::string getSrc() { return this->src; }
};


#endif