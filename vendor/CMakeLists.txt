set(SDL_TEST_LIBRARY OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(SDL)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3::SDL3-static)

add_subdirectory(imgui)
