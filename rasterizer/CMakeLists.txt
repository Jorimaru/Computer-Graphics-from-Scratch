add_executable(rasterizer
  src/main.c
  src/window.c
)

target_configure_executable(rasterizer)

find_library(OPENGL_LIBRARY OpenGL REQUIRED)

target_link_libraries(rasterizer PRIVATE
  glfw
  "${OPENGL_LIBRARY}"
  stb_image
)
