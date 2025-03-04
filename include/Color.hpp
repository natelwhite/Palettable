#pragma once
#include "imgui.h"
#include <string>

struct Color
{
  Color();
  ImVec4 raw; // r, g, b, a
  ImVec4 temp; // for storing user input from color picker
  bool altered {false}; // whether or not raw has changed
  bool alive {true};
  void show(const char *identity, const ImVec2 &pos, const ImVec2 &size); // display color dear imgui window
  std::string getString(); // returns color value in string format

  // flags for Imgui widgets/windows
  const static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
  const static ImGuiWindowFlags color_window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
  const static ImGuiColorEditFlags color_edit_flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoAlpha;
};

