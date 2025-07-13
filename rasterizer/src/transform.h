#pragma once

#include "linear_algebra.h"

typedef struct transform {
  vector3f_t translation;
  vector3f_t rotation;
  vector3f_t scale;
} transform_t;

matrix4f_t transform_to_matrix(transform_t* transform);

matrix4f_t translation_to_matrix(float translation_x,
                                 float translation_y,
                                 float translation_z);
matrix4f_t rotation_to_matrix(float rotation_x,
                              float rotation_y,
                              float rotation_z);
matrix4f_t scale_to_matrix(float scale_x, float scale_y, float scale_z);
