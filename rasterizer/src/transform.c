#include "transform.h"

#include <math.h>

static matrix4f_t translation_to_matrix(vector3f_t translation) {
  return (matrix4f_t){
    .elems = {
      1.0f, 0.0f, 0.0f, translation.x,
      0.0f, 1.0f, 0.0f, translation.y,
      0.0f, 0.0f, 1.0f, translation.z,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
}

static matrix4f_t rotation_to_matrix(vector3f_t rotation) {
  matrix4f_t rotation_x = {
    .elems = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, cosf(rotation.x), -sinf(rotation.x), 0.0f,
      0.0f, sinf(rotation.x), cosf(rotation.x), 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
  matrix4f_t rotation_y = {
    .elems = {
      cosf(rotation.y), 0.0f, sinf(rotation.y), 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      -sinf(rotation.y), 0.0f, cosf(rotation.y), 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
  matrix4f_t rotation_z = {
    .elems = {
      cosf(rotation.z), -sinf(rotation.z), 0.0f, 0.0f,
      sinf(rotation.z), cosf(rotation.z), 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
  
  matrix4f_t rotation_zy = matrix4f_mul(&rotation_z, &rotation_y);
  return matrix4f_mul(&rotation_zy, &rotation_x);
}

static matrix4f_t scale_to_matrix(vector3f_t scale) {
  return (matrix4f_t){
    .elems = {
      scale.x, 0.0f, 0.0f, 0.0f,
      0.0f, scale.y, 0.0f, 0.0f,
      0.0f, 0.0f, scale.z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };
}

matrix4f_t transform_to_matrix(transform_t* transform) {
  matrix4f_t matrix_scale = scale_to_matrix(transform->scale);
  matrix4f_t matrix_rotation = rotation_to_matrix(transform->rotation);
  matrix4f_t matrix_translation = translation_to_matrix(transform->translation);

  matrix4f_t matrix_rotation_scale = matrix4f_mul(&matrix_rotation, &matrix_scale);
  return matrix4f_mul(&matrix_translation, &matrix_rotation_scale);
}
