#include "renderer.h"

#include <math.h>
#include <stdlib.h>

#include "color.h"

static int maxi(int v0, int v1) {
  return v0 > v1 ? v0 : v1;
}

static void swap(int* v0, int* v1) {
  int t = *v0;
  *v0 = *v1;
  *v1 = t;
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

void draw_line(canvas_t* canvas, point2i_t p0, point2i_t p1) {
  vector2i_t v01 = point2i_sub_point2i(p1, p0);
  if (abs(v01.x) > abs(v01.y)) {
    if (p1.x < p0.x) {
      swap(&p0.x, &p1.x);
    }
    int num_values = maxi(abs(v01.x), 1);
    int* values = (int*)malloc(sizeof(int) * num_values);
    interpolate(p0.x, p0.y, p1.x, p1.y, values);
    for (int i = 0; i < num_values; i++) {
      canvas_set_pixel(canvas, p0.x + i, values[i], COLOR_BLACK);
    }
    free(values);
  } else {
    if (p1.y < p0.y) {
      swap(&p0.y, &p1.y);
    }
    int num_values = maxi(abs(v01.y), 1);
    int* values = (int*)malloc(sizeof(int) * num_values);
    interpolate(p0.y, p0.x, p1.y, p1.x, values);
    for (int i = 0; i < num_values; i++) {
      canvas_set_pixel(canvas, values[i], p0.y + i, COLOR_BLACK);
    }
    free(values);
  }
}
