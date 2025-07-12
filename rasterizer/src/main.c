#include <stdio.h>

#include <math.h>

#include "camera.h"
#include "canvas.h"
#include "image.h"
#include "linear_algebra.h"
#include "model.h"
#include "scene.h"
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

  point3f_t vertices[8] = {
    { .x = -0.5f, .y = -0.5f, .z = -0.5f }, // front bottom left
    { .x = 0.5f, .y = -0.5f, .z = -0.5f }, // front bottom right
    { .x = -0.5f, .y = 0.5f, .z = -0.5f }, // front top left
    { .x = 0.5f, .y = 0.5f, .z = -0.5f }, // front top right
    { .x = -0.5f, .y = -0.5f, .z = 0.5f }, // back bottom left
    { .x = 0.5f, .y = -0.5f, .z = 0.5f }, // back bottom right
    { .x = -0.5f, .y = 0.5f, .z = 0.5f }, // back top left
    { .x = 0.5f, .y = 0.5f, .z = 0.5f }, // back top right
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

  model_t model = {
    .vertices = vertices,
    .triangles = triangles,
    .num_vertices = 8,
    .num_triangles = 12,
  };

  instance_t instance = {
    .model = &model,
    .transform = {
      .translation = { .x = 0.0f, .y = 0.0f, .z = 5.5f },
      .rotation = { .x = 0.0f, .y = 0.0f, .z = 0.0f },
      .scale = { .x = 1.0f, .y = 1.0f, .z = 1.0f },
    },
  };

  scene_t scene = {
    .camera = {
      .width = VIEWPORT_WIDTH,
      .height = VIEWPORT_HEIGHT,
      .d = 1.0f,
    },
    .instances = &instance,
    .num_instances = 1,
  };

  while (!window_is_close_button_pressed()) {
    canvas_clear(&canvas, COLOR_WHITE);
    instance.transform.rotation.y += 0.01f;
    instance.transform.rotation.x += 0.02f;
    instance.transform.translation.x = sinf(instance.transform.rotation.y) * 2;
    render_scene(&canvas, &scene);
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
