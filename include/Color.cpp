#include "Color.hpp"
#include <iostream>

Color::Color() {
  int r = rand() % 101;
  int g = rand() % 101;
  int b = rand() % 101;
  this->raw = {static_cast<float>(r) / 100.0f, static_cast<float>(g) / 100.0f, static_cast<float>(b) / 100.0f, 1.0f};
  this->temp = this->raw;
}

void Color::show(const char *identity, const ImVec2 &pos, const ImVec2 &size) {
  // input window
  float input_height {56.0f};
  float color_window_height {size.y - 56.0f};
  ImGui::SetNextWindowPos(pos);
  ImGui::SetNextWindowSize({size.x, input_height});

  std::string color_edit_title = this->getString().data();
  std::string color_display_title = identity + color_edit_title;

  if (ImGui::Begin(identity, &this->alive, window_flags)) {
    ImGui::ColorEdit4(color_edit_title.data(), (float*)&this->temp, color_edit_flags);

    // all ImGui::IsItemXXX functions return true at inconvenient times
    // also, applying the value to the background color of the window closes the color picker
    // my fix:
    // track when the color picker value has changed
    // then, apply that color when the color picker closes

    if (ImGui::IsItemDeactivatedAfterEdit()) {
      this->altered = true;
    }

    std::string picker_id = this->getString() + "picker";
    if (this->altered && !ImGui::IsPopupOpen(picker_id.data())) {
      this->raw = this->temp;
      this->altered = false;
    }


    ImVec2 color_window_size {size.x, size.y - input_height};
    ImVec2 color_window_pos {pos.x, pos.y + input_height};

    // color window
    ImGui::SetNextWindowPos(color_window_pos);
    ImGui::SetNextWindowSize(color_window_size);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, this->raw);
    std::string display_title = color_edit_title + " display";

    if (ImGui::Begin(color_display_title.data(), &this->alive, color_window_flags)) {
      ImGui::PopStyleColor();
      ImGui::End();
    }

    ImGui::End();
  }
}

std::string Color::getString() {
  // lambda for rounding any floating point value to 2 decimals
  auto toIntString = [](const float &val) -> std::string {
    return std::to_string(static_cast<int>(val * 255));
  };
  std::string color = toIntString(this->raw.x) + ", " + toIntString(this->raw.y) + ", " + toIntString(this->raw.z);
  return color;
}

