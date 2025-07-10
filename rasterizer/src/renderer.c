#include "renderer.h"

#include <math.h>
#include <stdlib.h>

#include "color.h"

static int maxi(int v0, int v1) {
  return v0 > v1 ? v0 : v1;
}

static void point2i_swap(point2i_t* p0, point2i_t* p1) {
  point2i_t pt = *p0;
  *p0 = *p1;
  *p1 = pt;
}

static void vertex2_swap(vertex2_t* v0, vertex2_t* v1) {
  vertex2_t vt = *v0;
  *v0 = *v1;
  *v1 = vt;
}

static void interpolate(int i0, int d0, int i1, int d1, int* result) {
  if (i0 == i1) {
    result[0] = d0;
  } else {
    float a = (float)(d1 - d0) / (float)(i1 - i0);
    float d = (float)d0;
    for (int i = 0; i < (i1 - i0); i++) {
      result[i] = (int)d;
      d += a;
    }
  }
}

void draw_line(canvas_t* canvas, point2i_t p0, point2i_t p1, color_t color) {
  vector2i_t v01 = point2i_sub_point2i(p1, p0);
  if (abs(v01.x) > abs(v01.y)) {
    if (p1.x < p0.x) {
      point2i_swap(&p0, &p1);
    }
    int num_values = maxi(abs(v01.x), 1);
    int* values = (int*)malloc(sizeof(int) * num_values);
    interpolate(p0.x, p0.y, p1.x, p1.y, values);
    for (int i = 0; i < num_values; i++) {
      canvas_set_pixel(canvas, p0.x + i, values[i], color);
    }
    free(values);
  } else {
    if (p1.y < p0.y) {
      point2i_swap(&p0, &p1);
    }
    int num_values = maxi(abs(v01.y), 1);
    int* values = (int*)malloc(sizeof(int) * num_values);
    interpolate(p0.y, p0.x, p1.y, p1.x, values);
    for (int i = 0; i < num_values; i++) {
      canvas_set_pixel(canvas, values[i], p0.y + i, color);
    }
    free(values);
  }
}

void draw_wireframe_triangle(canvas_t* canvas,
                             point2i_t p0,
                             point2i_t p1,
                             point2i_t p2,
                             color_t color) {
  draw_line(canvas, p0, p1, color);
  draw_line(canvas, p1, p2, color);
  draw_line(canvas, p2, p0, color);
}

void draw_shaded_triangle(canvas_t* canvas,
                          vertex2_t v0,
                          vertex2_t v1,
                          vertex2_t v2,
                          color_t color) {
  // Sort the point from lowest y values to highest.
  if (v0.pos.y > v1.pos.y) {
    vertex2_swap(&v0, &v1);
  }
  if (v1.pos.y > v2.pos.y) {
    vertex2_swap(&v1, &v2);
  }
  if (v0.pos.y > v1.pos.y) {
    vertex2_swap(&v0, &v1);
  }

  int num_values = v2.pos.y - v0.pos.y;
  int* values = (int*)malloc(sizeof(int) * num_values * 2);

  interpolate(v0.pos.y, v0.pos.x, v2.pos.y, v2.pos.x, values);
  interpolate(v0.pos.y, v0.pos.x, v1.pos.y, v1.pos.x, values + num_values);
  interpolate(
    v1.pos.y,
    v1.pos.x,
    v2.pos.y,
    v2.pos.x,
    values + num_values + (v1.pos.y - v0.pos.y - 1));

  int* values_left;
  int* values_right;
  int m = num_values / 2;
  if (values[m] < (values + num_values)[m]) {
    values_left = values;
    values_right = values + num_values;
  } else {
    values_left = values + num_values;
    values_right = values;
  }

  for (int i = 0; i < num_values; i++) {
    for (int x = values_left[i]; x <= values_right[i]; x++) {
      canvas_set_pixel(canvas, x, v0.pos.y + i, color);
    }
  }

  free(values);
}
