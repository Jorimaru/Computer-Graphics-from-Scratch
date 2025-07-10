#pragma once

#include "canvas.h"
#include "color.h"
#include "linear_algebra.h"

typedef struct vertex2 {
  point2i_t pos;
  float h;
} vertex2_t;

void draw_line(canvas_t* canvas, point2i_t p0, point2i_t p1, color_t color);
void draw_wireframe_triangle(canvas_t* canvas,
                             point2i_t p0,
                             point2i_t p1,
                             point2i_t p2,
                             color_t color);
void draw_shaded_triangle(canvas_t* canvas,
                          vertex2_t v0,
                          vertex2_t v1,
                          vertex2_t v2,
                          color_t color);
