file(
  GLOB SOURCES
  main.cpp
  App.cpp
  Palette.cpp
  Color.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES})
