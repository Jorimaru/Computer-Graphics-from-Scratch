#include <stdio.h>

#include "camera.h"
#include "canvas.h"
#include "image.h"
#include "linear_algebra.h"
#include "renderer.h"
#include "window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_SCALE 1
#define CANVAS_WIDTH (WINDOW_WIDTH / WINDOW_SCALE)
#define CANVAS_HEIGHT (WINDOW_HEIGHT / WINDOW_SCALE)
#define VIEWPORT_WIDTH (VIEWPORT_HEIGHT * ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT))
#define VIEWPORT_HEIGHT 1.0f

int main(void) {
  if (!window_open("Rasterizer", WINDOW_WIDTH, WINDOW_HEIGHT)) {
    return 1;
  }

  canvas_t canvas = canvas_create(CANVAS_WIDTH, CANVAS_HEIGHT);
  canvas_clear(&canvas, COLOR_WHITE);

  camera_t camera = {
    .width = VIEWPORT_WIDTH,
    .height = VIEWPORT_HEIGHT,
    .d = 1.0f,
  };

  point3f_t vertices[8] = {
    { .x = -2.0f, .y = -0.5f, .z = 5.0f }, // front bottom left
    { .x = -1.0f, .y = -0.5f, .z = 5.0f }, // front bottom right
    { .x = -2.0f, .y = 0.5f, .z = 5.0f }, // front top left
    { .x = -1.0f, .y = 0.5f, .z = 5.0f }, // front top right
    { .x = -2.0f, .y = -0.5f, .z = 6.0f }, // back bottom left
    { .x = -1.0f, .y = -0.5f, .z = 6.0f }, // back bottom right
    { .x = -2.0f, .y = 0.5f, .z = 6.0f }, // back top left
    { .x = -1.0f, .y = 0.5f, .z = 6.0f }, // back top right
  };

  triangle_t triangles[12] = {
    { .indices = { 0, 1, 2 }, .color = COLOR_RED },
    { .indices = { 1, 3, 2 }, .color = COLOR_RED },
    { .indices = { 1, 5, 3 }, .color = COLOR_GREEN },
    { .indices = { 5, 7, 3 }, .color = COLOR_GREEN },
    { .indices = { 5, 4, 7 }, .color = COLOR_BLUE },
    { .indices = { 4, 6, 7 }, .color = COLOR_BLUE },
    { .indices = { 4, 0, 6 }, .color = COLOR_YELLOW },
    { .indices = { 0, 2, 6 }, .color = COLOR_YELLOW },
    { .indices = { 4, 5, 0 }, .color = COLOR_MAGENTA },
    { .indices = { 5, 1, 0 }, .color = COLOR_MAGENTA },
    { .indices = { 2, 3, 6 }, .color = COLOR_CYAN },
    { .indices = { 3, 7, 6 }, .color = COLOR_CYAN },
  };

  render_object(&canvas, &camera, vertices, 8, triangles, 12);

  while (!window_is_close_button_pressed()) {
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
