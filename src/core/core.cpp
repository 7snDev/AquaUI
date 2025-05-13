#include "core.h"

void init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("SDL init failed: %s\n", SDL_GetError());
    throw std::runtime_error(SDL_GetError());
  }

  if (TTF_Init() != 0) {
    printf("TTF init failed: %s\n", TTF_GetError());
    throw std::runtime_error(TTF_GetError());
  }

  // if (IMG_Init(IMG_INIT_PNG) != 0) {
  //   printf("IMG init failed: %s\n", IMG_GetError());
  //   throw std::runtime_error(IMG_GetError());
  // }

  // if (Mix_Init(MIX_INIT_MP3) != 0) {
  //   printf("Mix init failed: %s\n", Mix_GetError());
  //   throw std::runtime_error(Mix_GetError());
  // }
}

std::string searchFiles(const std::string &_path, const std::string &targetExtension, std::string filename)
{
  const std::filesystem::path path(_path);
  std::string file;
  try
  {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(path, std::filesystem::directory_options::skip_permission_denied))
    {
      if (entry.is_regular_file()
        &&entry.path().extension().string().find(targetExtension) != std::string::npos
        && (filename == "" ? true : entry.path().filename().string().find(filename) != std::string::npos))
      {
        file = entry.path().string();
      }
    }
  }
  catch (const std::filesystem::filesystem_error &ex)
  {
    throw std::runtime_error(ex.what());
  };
  if (file == "")
  {
    throw std::runtime_error("FileSearcher: File not found");
  }
  return file;
}

std::string getFont(std::string fontsdir) {
  std::string fonts[] = {"Arial", "arial", "Ubuntu-C", ""};
  std::string fontPath = "";
  for (auto font : fonts) {
    if (fontPath != "")
    {
      return fontPath;
    }
    try { fontPath = searchFiles(fontsdir, ".ttf", font); }
    catch(const std::exception& e) { printf("%s\n", e.what()); }
    if (fontPath == "")
    {
      try { fontPath = searchFiles(fontsdir, ".otf", font); }
      catch(const std::exception& e) { printf("%s\n", e.what()); }
    }
  }
  if (fontPath != "")
    return fontPath;
  throw std::runtime_error("There is no font");
}

std::string getFontDir() {
  if (AQUAUI_PLATFORM == "Linux")
  {
    return "/usr/share/fonts/truetype/";
  } else if (AQUAUI_PLATFORM == "Windows")
  {
    return "C:\\Windows\\Fonts\\";
  } else if (AQUAUI_PLATFORM == "MacOS")
  {
    return "/Library/Fonts/";
  }
  throw std::runtime_error("platform not supported");
}

TTF_Font* searchFont(int FontSize = 24) {
  std::string fontsdir = getFontDir();
  TTF_Font* font = TTF_OpenFont(getFont(fontsdir).c_str(), FontSize);
  if (font != NULL)
    return font;
  throw std::runtime_error("TTF_FONT: Font not found");
}

Window::Window(){
  init();
  this->window = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_HIDDEN);
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  this->font = searchFont(this->fontSize);
}

Window::Window(std::string title, int width, int height){
  init();
  this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN);
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  this->font = searchFont();
  this->fontSize = 50;
}

Window::Window(std::string title, int width, int height, int x, int y){
  init();
  this->window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_HIDDEN);
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  this->font = searchFont(this->fontSize);
}

Window::Window(std::string title){
  init();
  this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_HIDDEN);
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  this->font = searchFont(this->fontSize);
}

Window::~Window(){
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  TTF_Quit();
  SDL_Quit();
}

void Window::mainLoop() {
  SDL_Event event;
  bool running = true;
  SDL_ShowWindow(this->window);
  while (running) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) running = false;
      for (auto widget : widgets)
        widget->handleEvent(&event);
    }
    this->update();
    SDL_Delay(16);
  }
}

Widget *Window::getWidget(std::string id) {
  for (auto widget : widgets) {
    if (widget->id == id)
      return widget;
  }
  return nullptr;
}

void Window::update() {
  SDL_SetRenderDrawColor(this->renderer, this->background_Color.r, this->background_Color.g, this->background_Color.b, this->background_Color.a);
  SDL_RenderClear(this->renderer);
  for (auto widget : widgets) {
    widget->render(this);
  }
  SDL_RenderPresent(this->renderer);
}

void Window::updateWindow() {
  SDL_SetWindowSize(this->window, this->width, this->height);
  SDL_SetWindowPosition(this->window, this->x, this->y);
  SDL_SetWindowTitle(this->window, this->title.c_str());
}

void Window::addWidget(Widget* widget) {
  widgets.push_back(widget);
}

void Window::setFontSize(int fontSize) {
  this->fontSize = fontSize; 
  this->font = searchFont(this->fontSize);
}

Widget::Widget(int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

Widget::~Widget() {  }

Widget::Widget() {
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;
}

void Widget::render(Window* window) {  }

void Widget::handleEvent(SDL_Event* event) {  }