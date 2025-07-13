#include "transform.h"

#include <math.h>

matrix4f_t translation_to_matrix(float translation_x,
                                 float translation_y,
                                 float translation_z) {
  return (matrix4f_t){
    .elems = {
      1.0f, 0.0f, 0.0f, translation_x,
      0.0f, 1.0f, 0.0f, translation_y,
      0.0f, 0.0f, 1.0f, translation_z,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
}

matrix4f_t rotation_to_matrix(float rotation_x,
                              float rotation_y,
                              float rotation_z) {
  matrix4f_t matrix_rotation_x = {
    .elems = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, cosf(rotation_x), -sinf(rotation_x), 0.0f,
      0.0f, sinf(rotation_x), cosf(rotation_x), 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
  matrix4f_t matrix_rotation_y = {
    .elems = {
      cosf(rotation_y), 0.0f, sinf(rotation_y), 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      -sinf(rotation_y), 0.0f, cosf(rotation_y), 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
  matrix4f_t matrix_rotation_z = {
    .elems = {
      cosf(rotation_z), -sinf(rotation_z), 0.0f, 0.0f,
      sinf(rotation_z), cosf(rotation_z), 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
  
  matrix4f_t matrix_rotation_zy =
    matrix4f_mul(&matrix_rotation_z, &matrix_rotation_y);
  return matrix4f_mul(&matrix_rotation_zy, &matrix_rotation_x);
}

matrix4f_t scale_to_matrix(float scale_x, float scale_y, float scale_z) {
  return (matrix4f_t){
    .elems = {
      scale_x, 0.0f, 0.0f, 0.0f,
      0.0f, scale_y, 0.0f, 0.0f,
      0.0f, 0.0f, scale_z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
}

matrix4f_t transform_to_matrix(transform_t* transform) {
  matrix4f_t matrix_scale = scale_to_matrix(
    transform->scale.x,
    transform->scale.y,
    transform->scale.z);
  matrix4f_t matrix_rotation = rotation_to_matrix(
    transform->rotation.x,
    transform->rotation.y,
    transform->rotation.z);
  matrix4f_t matrix_translation = translation_to_matrix(
    transform->translation.x,
    transform->translation.y,
    transform->translation.z);

  matrix4f_t matrix_rotation_scale =
    matrix4f_mul(&matrix_rotation, &matrix_scale);
  return matrix4f_mul(&matrix_translation, &matrix_rotation_scale);
}
