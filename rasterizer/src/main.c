#include <stdio.h>

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

int main(void) {
  if (!window_open("Rasterizer", WINDOW_WIDTH, WINDOW_HEIGHT)) {
    return 1;
  }

  canvas_t canvas = canvas_create(CANVAS_WIDTH, CANVAS_HEIGHT);
  canvas_clear(&canvas, COLOR_WHITE);

  vertex2_t v0 = { .pos = { .x = -200, .y = -250 }, .h = 0.5f };
  vertex2_t v1 = { .pos = { .x = 200, .y = 50 }, .h = 0.0f };
  vertex2_t v2 = { .pos = { .x = 20, .y = 250 }, .h = 1.0f };

  color_t green = { .r = 0, .g = 255, .b = 0, .a = 255 };

  draw_shaded_triangle(&canvas, v0, v1, v2, green);
  draw_wireframe_triangle(&canvas, v0.pos, v1.pos, v2.pos, COLOR_BLACK);

  while (!window_is_close_button_pressed()) {
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
