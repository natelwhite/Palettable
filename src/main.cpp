#include "App.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL2/SDL.h>

#include <string>
#include <iostream>
#include <array>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ beacuse of SDL_RenderGeometry() functions
#endif


int main(int, char**)
{
  App palettable;
  return palettable.run();
}
