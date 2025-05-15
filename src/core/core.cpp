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

  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("IMG init failed: %s\n", IMG_GetError());
    throw std::runtime_error(IMG_GetError());
  }

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
  this->window = SDL_CreateWindow("AquaUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_HIDDEN);
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  this->font = searchFont(this->fontSize);
}

Window::~Window(){
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  TTF_Quit();
  SDL_Quit();
}

void Window::mainLoop() {
  this->updateWindow();
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

void sortWidgets(std::vector<Widget*>* widgets) {
  std::sort(widgets->begin(), widgets->end(), [](Widget* a, Widget* b) {
    return a->getZIndex() < b->getZIndex();
  });
}

void Window::update() {
  SDL_SetRenderDrawColor(this->renderer, this->background_Color.r, this->background_Color.g, this->background_Color.b, this->background_Color.a);
  SDL_RenderClear(this->renderer);
  sortWidgets(&widgets);
  for (auto widget : widgets) {
    widget->render(this);
  }
  SDL_RenderPresent(this->renderer);
}

void Window::updateWindow() {
  if (this->width  > 0 && this->height > 0)
    SDL_SetWindowSize(this->window, this->width, this->height);
  if (this->x > 0 && this->y > 0)
    SDL_SetWindowPosition(this->window, this->x, this->y);
  if (this->icon != nullptr)
    SDL_SetWindowIcon(this->window, this->icon);
  if (title != "")
    SDL_SetWindowTitle(this->window, this->title.c_str());
  if (this->background_Color.a >= 0)
    SDL_SetWindowOpacity(this->window, this->background_Color.a / 255.0f);
  SDL_SetWindowResizable(this->window, SDL_bool(this->resizable));
  SDL_SetWindowFullscreen(this->window, this->fullscreen);
}

void Window::setFontSize(int fontSize) {
  this->fontSize = fontSize; 
  this->font = searchFont(this->fontSize);
}

void Widget::handleEvent(SDL_Event* event) {}
void Widget::render(Window* window) {}
Widget::Widget() {
  this->callback = new Callback();
}
