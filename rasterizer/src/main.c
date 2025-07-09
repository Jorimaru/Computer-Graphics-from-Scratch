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

  point2i_t p0 = { .x = -200, .y = -100 };
  point2i_t p1 = { .x = 240, .y = 120 };
  point2i_t p2 = { .x = -50, .y = -200 };
  point2i_t p3 = { .x = 60, .y = 240 };

  draw_line(&canvas, p0, p1);
  draw_line(&canvas, p2, p3);

  while (!window_is_close_button_pressed()) {
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
