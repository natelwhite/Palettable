#pragma once
#include "Palette.hpp"
#include <SDL3/SDL.h>
#include "imgui.h"

class App
{
  public:
    App(); // init imgui & SDL2 + create window & renderer
    int run(); // run main frame loop
    ~App(); // safely quit imgui & SDL2
  private:
    void show(); // show imgui widgets
    bool m_running = true;
    Palette m_palette {3, 3};

    // current value for rows and cols (linked with ImGui::InputInt instance)
    int m_palette_rows {3}, m_palette_cols {3};
    // color of screen wipe each frame
    const SDL_Color m_clear_color {51, 51, 51, 255};

    ImGuiIO m_io;
    SDL_Renderer *m_renderer;
    SDL_Window *m_window;

    // window flags
    const static ImGuiWindowFlags m_app_window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground;

    const static ImGuiWindowFlags m_tools_window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;

};

