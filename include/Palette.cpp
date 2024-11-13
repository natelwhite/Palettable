#include "Palette.hpp"
#include <iostream>

Palette::Palette(const int &t_rows, const int &t_cols)
  : m_rows(t_rows), m_cols(t_cols) {
  // create enough colors to fill the table
  std::srand(time(0)); // for random color generation
  m_colors.resize(m_rows * m_cols);
}

void Palette::newColor() {
  m_colors.emplace_back(Color());
}

void Palette::setRows(const int &t_rows) {
  m_rows = t_rows;
}

void Palette::setCols(const int &t_cols) {
  m_cols = t_cols;
}

void Palette::show(const ImVec2 &size, const ImVec2 &pos) {
  ImGui::SetNextWindowSize(size);
  ImGui::SetNextWindowPos(pos);

  if (ImGui::Begin("Palette", NULL, m_window_flags)) {
    int row { }, col { };
    ImVec2 color_size = {size.x / static_cast<float>(m_cols), size.y / static_cast<float>(m_rows)};
    // color data may mutate, don't use foreach
    for (int i = 0; i < m_colors.size(); ++i) {
      // see if color was removed
      if (!m_colors.at(i).alive) {
        m_colors.erase(m_colors.begin() + i);
        break;
      }

      // calc pos based on col, row, and color_size
      ImVec2 color_pos = {pos.x + col * color_size.x, pos.y + row * color_size.y};
      std::string name = std::to_string(row) + 'x' + std::to_string(col) + ": ";

      // show color
      m_colors.at(i).show(name.data(), color_pos, color_size);

      // adjust row & col to follow table structure
      ++col;
      if (col == m_cols) {
        col = 0;
        ++row;
      }
    }
    ImGui::End();
  }
}
