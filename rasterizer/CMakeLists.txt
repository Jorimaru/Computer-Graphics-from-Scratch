add_executable(rasterizer
  src/camera.c
  src/canvas.c
  src/color.c
  src/image.c
  src/linear_algebra.c
  src/main.c
  src/renderer.c
  src/window.c
)

target_configure_executable(rasterizer)

find_library(OPENGL_LIBRARY OpenGL REQUIRED)

target_link_libraries(rasterizer PRIVATE
  glfw
  "${OPENGL_LIBRARY}"
  stb_image
)
