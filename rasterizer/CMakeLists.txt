add_executable(rasterizer
  src/main.c)

target_configure_executable(rasterizer)

target_link_libraries(rasterizer PRIVATE
  glfw
  stb_image)
