#pragma once

#include "color.h"
#include "linear_algebra.h"
#include "transform.h"

typedef struct triangle {
  int indices[3];
  color_t color;
} triangle_t;

typedef struct model {
  point3f_t* vertices;
  triangle_t* triangles;
  int num_vertices;
  int num_triangles;
} model_t;
