#pragma once

#include "canvas.h"
#include "linear_algebra.h"

typedef struct camera {
  float width;
  float height;
  float d;
} camera_t;

point2i_t viewport_to_canvas(camera_t* camera, canvas_t* canvas, point3f_t p);

point2i_t project_vertex(camera_t* camera, canvas_t* canvas, point3f_t p);
