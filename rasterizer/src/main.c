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

  point3f_t ftl = { .x = -2.0f, .y = -0.5f, .z = 5.0f };
  point3f_t ftr = { .x = -1.0f, .y = -0.5f, .z = 5.0f };
  point3f_t fbl = { .x = -2.0f, .y = 0.5f, .z = 5.0f };
  point3f_t fbr = { .x = -1.0f, .y = 0.5f, .z = 5.0f };

  point3f_t btl = { .x = -2.0f, .y = -0.5f, .z = 6.0f };
  point3f_t btr = { .x = -1.0f, .y = -0.5f, .z = 6.0f };
  point3f_t bbl = { .x = -2.0f, .y = 0.5f, .z = 6.0f };
  point3f_t bbr = { .x = -1.0f, .y = 0.5f, .z = 6.0f };

  draw_line(&canvas, project_vertex(&camera, &canvas, ftl), project_vertex(&camera, &canvas, ftr), COLOR_BLUE);
  draw_line(&canvas, project_vertex(&camera, &canvas, ftl), project_vertex(&camera, &canvas, fbl), COLOR_BLUE);
  draw_line(&canvas, project_vertex(&camera, &canvas, ftr), project_vertex(&camera, &canvas, fbr), COLOR_BLUE);
  draw_line(&canvas, project_vertex(&camera, &canvas, fbl), project_vertex(&camera, &canvas, fbr), COLOR_BLUE);

  draw_line(&canvas, project_vertex(&camera, &canvas, btl), project_vertex(&camera, &canvas, btr), COLOR_RED);
  draw_line(&canvas, project_vertex(&camera, &canvas, btl), project_vertex(&camera, &canvas, bbl), COLOR_RED);
  draw_line(&canvas, project_vertex(&camera, &canvas, btr), project_vertex(&camera, &canvas, bbr), COLOR_RED);
  draw_line(&canvas, project_vertex(&camera, &canvas, bbl), project_vertex(&camera, &canvas, bbr), COLOR_RED);

  draw_line(&canvas, project_vertex(&camera, &canvas, ftl), project_vertex(&camera, &canvas, btl), COLOR_GREEN);
  draw_line(&canvas, project_vertex(&camera, &canvas, ftr), project_vertex(&camera, &canvas, btr), COLOR_GREEN);
  draw_line(&canvas, project_vertex(&camera, &canvas, fbl), project_vertex(&camera, &canvas, bbl), COLOR_GREEN);
  draw_line(&canvas, project_vertex(&camera, &canvas, fbr), project_vertex(&camera, &canvas, bbr), COLOR_GREEN);

  while (!window_is_close_button_pressed()) {
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
