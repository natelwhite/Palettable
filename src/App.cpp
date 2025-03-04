#include "App.hpp"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

App::App()
{
  // init SDL3 systems
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("Error: %s\n", SDL_GetError());
  }

  // enable native IME
#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

  // create window
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
  m_window = SDL_CreateWindow("Palettable", 1280, 720, window_flags);
  if (m_window == nullptr) {
    printf("Error: SDL_CreateWindow0(): %s\n", SDL_GetError());
  }

  // create render backend
  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (m_renderer == nullptr) {
    SDL_Log("Error creating SDL_Renderer!");
  }

  // setup dear imgui context
  IMGUI_CHECKVERSION();
  ImGuiContext* context = ImGui::CreateContext();
  ImGui::SetCurrentContext(context);

  // link imgui to sdl2
  ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
  ImGui_ImplSDLRenderer3_Init(m_renderer);

  // setup io
  m_io = ImGui::GetIO(); (void)m_io;
  m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // setup dear imgui style
  ImGui::StyleColorsDark();
}

int App::run() {
  // main loop
  SDL_Event event;
  while (m_running) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      switch(event.type) {
        case SDL_EVENT_QUIT:
          m_running = false;
          break;
      }
    }

    // start dear imgui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // show app window
    this->show();

    ImGui::EndFrame();

    // Rendering
    ImGui::Render();
    SDL_SetRenderScale(m_renderer, m_io.DisplayFramebufferScale.x, m_io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(m_renderer, m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    SDL_RenderClear(m_renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
    SDL_RenderPresent(m_renderer);
  }
  return 0;
}

App::~App() {
  // cleanup
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void App::show() {
  // make window fill viewport
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  
  if (ImGui::Begin("Palettable", &m_running, m_app_window_flags)) {
    // calculate window positions and sizes
    ImVec2 app_size = ImGui::GetWindowSize();
    ImVec2 tools_pos {0.0f, 0.0f};
    ImVec2 tools_size {app_size.x * 0.2f, app_size.y};

    // toolbar
    ImGui::SetNextWindowPos(tools_pos);
    ImGui::SetNextWindowSize(tools_size, ImGuiCond_Once);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
    if (ImGui::Begin("Toolbar", NULL, m_tools_window_flags)) {
      ImGui::PopStyleVar();
      tools_size = ImGui::GetWindowSize();

      if (ImGui::Button("Add Color")) {
        m_palette.newColor();
      }

      // inputs for changing num of rows & cols
      // nums & rows is int type for the ImGui::InputInt
      // but it has a hard limit of 255 (Palette::m_rows & Palette::m_cols are both Uint8)
      ImGui::InputInt("Rows", &m_palette_rows);
      if (ImGui::IsItemEdited()) {
        if (m_palette_rows < 1) {
          m_palette_rows = 1;
        }
        m_palette.setRows(m_palette_rows);
      }

      ImGui::InputInt("Columns", &m_palette_cols);
      if (ImGui::IsItemEdited()) {
        if (m_palette_cols < 1) {
          m_palette_rows = 1;
        }
        m_palette.setCols(m_palette_cols);
      }

      ImGui::End();
    }

    // show palette
    float left_margin = 2.0f;
    ImVec2 palette_pos = {tools_size.x + left_margin, 0.0f};
    ImVec2 palette_size = {app_size.x - (tools_size.x + left_margin), app_size.y};
    m_palette.show(palette_size, palette_pos);

    ImGui::End();
  }
}

