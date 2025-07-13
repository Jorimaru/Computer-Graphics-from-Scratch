#pragma once

#include "canvas.h"
#include "linear_algebra.h"

typedef struct camera {
  point3f_t position;
  vector3f_t forward;
  vector3f_t up;
  float viewport_width;
  float viewport_height;
  float viewport_distance;
} camera_t;

point2i_t viewport_to_canvas(camera_t* camera, canvas_t* canvas, point3f_t p);
point2i_t* project_vertices(camera_t* camera,
                            canvas_t* canvas,
                            point3f_t* vertices,
                            int num_vertices);

matrix4f_t camera_projection_matrix(camera_t* camera);
matrix4f_t camera_view_matrix(camera_t* camera);
matrix4f_t camera_projection_view_matrix(camera_t* camera);

void camera_rotate(camera_t* camera, float x, float y, float z);
void camera_move_forward(camera_t* camera, float speed);
void camera_move_up(camera_t* camera, float speed);
void camera_move_right(camera_t* camera, float speed);
