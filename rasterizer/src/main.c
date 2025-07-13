#include <stdio.h>

#include <math.h>

#include "camera.h"
#include "canvas.h"
#include "image.h"
#include "input.h"
#include "linear_algebra.h"
#include "model.h"
#include "scene.h"
#include "window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_SCALE 1
#define CANVAS_WIDTH (WINDOW_WIDTH / WINDOW_SCALE)
#define CANVAS_HEIGHT (WINDOW_HEIGHT / WINDOW_SCALE)
#define VIEWPORT_WIDTH \
  (VIEWPORT_HEIGHT * ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT))
#define VIEWPORT_HEIGHT 1.0f
#define CAMERA_ROTATE_SPEED 0.001f
#define CAMERA_MOVE_SPEED 0.1f

#define array_length(a) (sizeof(a) / sizeof(a[0]))

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
    .num_vertices = array_length(vertices),
    .num_triangles = array_length(triangles),
  };

  instance_t instances[2] = {
    {
      .model = &model,
      .transform = {
        .translation = { .x = 0.0f, .y = 1.0f, .z = 0.0f },
        .rotation = { .x = 0.0f, .y = 0.0f, .z = 0.0f },
        .scale = { .x = 1.0f, .y = 1.0f, .z = 1.0f },
      },
    },
    {
      .model = &model,
      .transform = {
        .translation = { .x = 0.0f, .y = -1.0f, .z = 0.0f },
        .rotation = { .x = 0.0f, .y = 0.0f, .z = 0.0f },
        .scale = { .x = 1.0f, .y = 1.0f, .z = 1.0f },
      },
    },
  };

  scene_t scene = {
    .camera = {
      .position = { .x = 0.0f, .y = 0.0f, .z = -5.5f },
      .forward = VECTOR3F_AXIS_Z,
      .up = VECTOR3F_AXIS_Y,
      .viewport_width = VIEWPORT_WIDTH,
      .viewport_height = VIEWPORT_HEIGHT,
      .viewport_distance = 1.0f,
    },
    .instances = instances,
    .num_instances = array_length(instances),
  };

  while (!window_is_close_button_pressed()) {
    camera_rotate(
      &scene.camera,
      rotate_vertically() * CAMERA_ROTATE_SPEED,
      rotate_horizontally() * CAMERA_ROTATE_SPEED,
      0.0f);

    if (move_up()) {
      camera_move_up(&scene.camera, CAMERA_MOVE_SPEED);
    }
    if (move_down()) {
      camera_move_up(&scene.camera, -CAMERA_MOVE_SPEED);
    }
    if (move_right()) {
      camera_move_right(&scene.camera, CAMERA_MOVE_SPEED);
    }
    if (move_left()) {
      camera_move_right(&scene.camera, -CAMERA_MOVE_SPEED);
    }
    if (move_forward()) {
      camera_move_forward(&scene.camera, CAMERA_MOVE_SPEED);
    }
    if (move_backward()) {
      camera_move_forward(&scene.camera, -CAMERA_MOVE_SPEED);
    }

    canvas_clear(&canvas, COLOR_WHITE);

    instances[0].transform.rotation.y += 0.01f;
    instances[0].transform.rotation.x += 0.02f;
    instances[0].transform.translation.x =
      sinf(instances[0].transform.rotation.y) * 2;

    instances[1].transform.rotation.y -= 0.01f;
    instances[1].transform.rotation.x -= 0.02f;
    instances[1].transform.translation.x =
      sinf(instances[1].transform.rotation.y) * 2;

    render_scene(&canvas, &scene);
    window_draw_canvas(&canvas);
  }

  canvas_destroy(&canvas);
  window_close();
}
