#include "renderer.h"

#include <math.h>
#include <stdlib.h>

#include "color.h"

static int maxi(int v0, int v1) {
  return v0 > v1 ? v0 : v1;
}

static int mini(int v0, int v1) {
  return v0 < v1 ? v0 : v1;
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

static void interpolate(int i0, float d0, int i1, float d1, float* result) {
  if (i0 == i1) {
    result[0] = d0;
  } else {
    float a = (d1 - d0) / (i1 - i0);
    float d = d0;
    for (int i = 0; i < (i1 - i0); i++) {
      result[i] = d;
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
    float* values = (float*)malloc(sizeof(values[0]) * num_values);
    interpolate(p0.x, p0.y, p1.x, p1.y, values);
    for (int i = 0; i < num_values; i++) {
      canvas_set_pixel(canvas, p0.x + i, (int)values[i], color);
    }
    free(values);
  } else {
    if (p1.y < p0.y) {
      point2i_swap(&p0, &p1);
    }
    int num_values = maxi(abs(v01.y), 1);
    float* values = (float*)malloc(sizeof(values[0]) * num_values);
    interpolate(p0.y, p0.x, p1.y, p1.x, values);
    for (int i = 0; i < num_values; i++) {
      canvas_set_pixel(canvas, (int)values[i], p0.y + i, color);
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

  int num_xs = v2.pos.y - v0.pos.y;
  float* xs = (float*)malloc(sizeof(xs[0]) * num_xs * 4);
  float* hs = xs + (num_xs * 2);

  interpolate(v0.pos.y, v0.pos.x, v2.pos.y, v2.pos.x, xs);
  interpolate(v0.pos.y, v0.pos.x, v1.pos.y, v1.pos.x, xs + num_xs);
  interpolate(
    v1.pos.y,
    v1.pos.x,
    v2.pos.y,
    v2.pos.x,
    xs + num_xs + (v1.pos.y - v0.pos.y - 1));

  interpolate(v0.pos.y, v0.h, v2.pos.y, v2.h, hs);
  interpolate(v0.pos.y, v0.h, v1.pos.y, v1.h, hs + num_xs);
  interpolate(
    v1.pos.y,
    v1.h,
    v2.pos.y,
    v2.h,
    hs + num_xs + (v1.pos.y - v0.pos.y - 1));

  float* xs_left;
  float* xs_right;
  float* hs_left;
  float* hs_right;
  int m = num_xs / 2;
  if (xs[m] < (xs + num_xs)[m]) {
    xs_left = xs;
    xs_right = xs + num_xs;
    hs_left = hs;
    hs_right = hs + num_xs;
  } else {
    xs_left = xs + num_xs;
    xs_right = xs;
    hs_left = hs + num_xs;
    hs_right = hs;
  }

  int num_hs =
    maxi(maxi(v0.pos.x, v1.pos.x), v2.pos.x) -
    mini(mini(v0.pos.x, v1.pos.x), v2.pos.x);
  float* line_hs = (float*)malloc(sizeof(float) * num_hs);

  for (int i = 0; i < num_xs; i++) {
    interpolate(xs_left[i], hs_left[i], xs_right[i], hs_right[i], line_hs);
    for (int j = 0; j < (xs_right[i] - xs_left[i]); j++) {
      canvas_set_pixel(
        canvas, xs_left[i] + j, v0.pos.y + i, color_scale(color, line_hs[j]));
    }
  }

  free(line_hs);
  free(xs);
}

void render_object(canvas_t* canvas,
                   camera_t* camera,
                   point3f_t* vertices,
                   int num_vertices,
                   triangle_t* triangles,
                   int num_triangles) {
  point2i_t* projected_vertices =
    (point2i_t*)malloc(sizeof(point2i_t) * num_vertices);
  for (int i = 0; i < num_vertices; i++) {
    projected_vertices[i] = project_vertex(camera, canvas, vertices[i]);
  }
  for (int i = 0; i < num_triangles; i++) {
    render_triangle(canvas, &triangles[i], projected_vertices);
  }
  free(projected_vertices);
}

void render_triangle(canvas_t* canvas,
                     triangle_t* triangle,
                     point2i_t* projected_vertices) {
  draw_wireframe_triangle(
    canvas,
    projected_vertices[triangle->indices[0]],
    projected_vertices[triangle->indices[1]],
    projected_vertices[triangle->indices[2]],
    triangle->color);
}
