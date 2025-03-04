cmake_minimum_required(VERSION 3.28)

project(Palettable)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generate compiler_commands.json for clangd

add_executable(${PROJECT_NAME})

add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(include)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
