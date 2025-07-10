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

  point2i_t p0 = { .x = -200, .y = -250 };
  point2i_t p1 = { .x = 200, .y = 50 };
  point2i_t p2 = { .x = 20, .y = 250 };

  draw_wireframe_triangle(&canvas, p0, p1, p2, COLOR_BLACK);

  while (!window_is_close_button_pressed()) {
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
