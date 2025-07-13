#include "linear_algebra.h"

#include <math.h>

point2i_t point2i_add(point2i_t lhs, vector2i_t rhs) {
  return (point2i_t){
    .x = lhs.x + rhs.x,
    .y = lhs.y + rhs.y,
  };
}

point2i_t point2i_sub(point2i_t lhs, vector2i_t rhs) {
  return (point2i_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
  };
}

vector2i_t point2i_sub_point2i(point2i_t lhs, point2i_t rhs) {
  return (vector2i_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
  };
}

vector2i_t vector2i_invert(vector2i_t vector) {
  return (vector2i_t){
    .x = -vector.x,
    .y = -vector.y,
  };
}

vector2i_t vector2i_add(vector2i_t lhs, vector2i_t rhs) {
  return (vector2i_t){
    .x = lhs.x + rhs.x,
    .y = lhs.y + rhs.y,
  };
}

vector2i_t vector2i_sub(vector2i_t lhs, vector2i_t rhs) {
  return (vector2i_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
  };
}

point3f_t point3f_add(point3f_t lhs, vector3f_t rhs) {
  return (point3f_t){
    .x = lhs.x + rhs.x,
    .y = lhs.y + rhs.y,
    .z = lhs.z + rhs.z,
  };
}

point3f_t point3f_sub(point3f_t lhs, vector3f_t rhs) {
  return (point3f_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
    .z = lhs.z - rhs.z,
  };
}

vector3f_t point3f_sub_point3f(point3f_t lhs, point3f_t rhs) {
  return (vector3f_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
    .z = lhs.z - rhs.z,
  };
}

point3f_t point3f_scale(point3f_t point, float scale) {
  return (point3f_t){
    .x = point.x * scale,
    .y = point.y * scale,
    .z = point.z * scale,
  };
}

float vector3f_length_squared(vector3f_t vector) {
  return vector3f_dot(vector, vector);
}

float vector3f_length(vector3f_t vector) {
  return sqrtf(vector3f_length_squared(vector));
}

vector3f_t vector3f_normalize(vector3f_t vector) {
  float length = vector3f_length(vector);
  return length == 0.0f ? vector : vector3f_scale(vector, 1.0f / length);
}

float vector3f_dot(vector3f_t lhs, vector3f_t rhs) {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

vector3f_t vector3f_cross(vector3f_t lhs, vector3f_t rhs) {
  return (vector3f_t){
    .x = (lhs.y * rhs.z) - (lhs.z * rhs.y),
    .y = (lhs.z * rhs.x) - (lhs.x * rhs.z),
    .z = (lhs.x * rhs.y) - (lhs.y * rhs.x),
  };
}

vector3f_t vector3f_invert(vector3f_t vector) {
  return vector3f_scale(vector, -1.0f);
}

vector3f_t vector3f_add(vector3f_t lhs, vector3f_t rhs) {
  return (vector3f_t){
    .x = lhs.x + rhs.x,
    .y = lhs.y + rhs.y,
    .z = lhs.z + rhs.z,
  };
}

vector3f_t vector3f_sub(vector3f_t lhs, vector3f_t rhs) {
  return (vector3f_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
    .z = lhs.z - rhs.z,
  };
}

vector3f_t vector3f_scale(vector3f_t vector, float scale) {
  return (vector3f_t){
    .x = vector.x * scale,
    .y = vector.y * scale,
    .z = vector.z * scale,
  };
}

matrix4f_t matrix4f_transpose(matrix4f_t* matrix) {
  matrix4f_t result;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      result.at[y][x] = matrix->at[x][y];
    }
  }

  return result;
}

matrix4f_t matrix4f_inverse(matrix4f_t* matrix) {
  return matrix4f_scale(matrix, -1.0f);
}

matrix4f_t matrix4f_add(matrix4f_t* lhs, matrix4f_t* rhs) {
  matrix4f_t result;
  for (int i = 0; i < 16; i++) {
    result.elems[i] = lhs->elems[i] + rhs->elems[i];
  }

  return result;
}

matrix4f_t matrix4f_sub(matrix4f_t* lhs, matrix4f_t* rhs) {
  matrix4f_t result;
  for (int i = 0; i < 16; i++) {
    result.elems[i] = lhs->elems[i] - rhs->elems[i];
  }

  return result;
}

matrix4f_t matrix4f_mul(matrix4f_t* lhs, matrix4f_t* rhs) {
  matrix4f_t result = {};
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      for (int i = 0; i < 4; i++) {
        result.at[x][y] += lhs->at[x][i] * rhs->at[i][y];
      }
    }
  }

  return result;
}

matrix4f_t matrix4f_scale(matrix4f_t* matrix, float scale) {
  matrix4f_t result;
  for (int i = 0; i < 16; i++) {
    result.elems[i] = matrix->elems[i] * scale;
  }

  return result;
}

point3f_t matrix4f_transform_point3f(matrix4f_t* matrix, point3f_t point) {
  point3f_t result = {};
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      result.at[x] += matrix->at[x][y] * point.at[y];
    }
    result.at[x] += matrix->at[x][3];
  }

  return point3f_scale(result, 1.0f / matrix->at[3][3]);
}

vector3f_t matrix4f_transform_vector3f(matrix4f_t* matrix, vector3f_t vector) {
  vector3f_t result = {};
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      result.at[x] += matrix->at[x][y] * vector.at[y];
    }
  }

  return result;
}
