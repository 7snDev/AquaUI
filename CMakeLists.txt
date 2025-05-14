cmake_minimum_required(VERSION 3.14)
project(AquaUI)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

pkg_check_modules(tinyxml2 REQUIRED tinyxml2)

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS}
  ${tinyxml2_INCLUDE_DIRS}
  src
)

add_executable(app
  src/main.cpp
  src/core/core.cpp
  # src/core/xmlBuilder.cpp
  src/Widgets/Label.cpp
  src/Widgets/Button.cpp
)

target_link_libraries(app
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  ${tinyxml2_LIBRARIES}
)
