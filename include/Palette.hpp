#pragma once
#include "Color.hpp"

#include "imgui.h"

#include <vector>
#include <stdlib.h>

class Palette
{
  // display a table of colors
  public:
    Palette(const int &t_rows, const int &t_cols); // allocate color structs
    void show(const ImVec2 &size, const ImVec2 &pos); // display palette window
    // mutators
    void setRows(const int &t_rows);
    void setCols(const int &t_cols);
    void newColor();
  private:
    int m_rows;
    int m_cols;
    std::vector<Color> m_colors;

    // window flags
    const static ImGuiWindowFlags m_window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground;
};
