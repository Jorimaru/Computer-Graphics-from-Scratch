#pragma once

#include "linear_algebra.h"

typedef struct transform {
  vector3f_t translation;
  vector3f_t rotation;
  vector3f_t scale;
} transform_t;

matrix4f_t transform_to_matrix(transform_t* transform);
