#include "App.hpp"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ beacuse of SDL_RenderGeometry() functions
#endif


int main(int, char**)
{
  App palettable;
  return palettable.run();
}
