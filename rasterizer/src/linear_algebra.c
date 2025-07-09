#include "linear_algebra.h"

#include <math.h>

point_t point_add(point_t lhs, vector_t rhs) {
  return (point_t){
    .x = lhs.x + rhs.x,
    .y = lhs.y + rhs.y,
    .z = lhs.z + rhs.z,
  };
}

point_t point_sub(point_t lhs, vector_t rhs) {
  return (point_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
    .z = lhs.z - rhs.z,
  };
}

float vector_length_squared(vector_t vector) {
  return vector_dot(vector, vector);
}

float vector_length(vector_t vector) {
  return sqrtf(vector_length_squared(vector));
}

vector_t vector_normalize(vector_t vector) {
  float length = vector_length(vector);
  return length == 0.0f ? vector : vector_scale(vector, 1.0f / length);
}

float vector_dot(vector_t lhs, vector_t rhs) {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

vector_t vector_cross(vector_t lhs, vector_t rhs) {
  return (vector_t){
    .x = (lhs.y * rhs.z) - (lhs.z * rhs.y),
    .y = (lhs.z * rhs.x) - (lhs.x * rhs.z),
    .z = (lhs.x * rhs.y) - (lhs.y * rhs.x),
  };
}

vector_t vector_invert(vector_t vector) {
  return vector_scale(vector, -1.0f);
}

vector_t vector_add(vector_t lhs, vector_t rhs) {
  return (vector_t){
    .x = lhs.x + rhs.x,
    .y = lhs.y + rhs.y,
    .z = lhs.z + rhs.z,
  };
}

point_t vector_sub(vector_t lhs, vector_t rhs) {
  return (point_t){
    .x = lhs.x - rhs.x,
    .y = lhs.y - rhs.y,
    .z = lhs.z - rhs.z,
  };
}

vector_t vector_scale(vector_t vector, float scale) {
  return (vector_t){
    .x = vector.x * scale,
    .y = vector.y * scale,
    .z = vector.z * scale,
  };
}

matrix_t matrix_transpose(matrix_t* matrix) {
  matrix_t result;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      result.at[y][x] = matrix->at[x][y];
    }
  }

  return result;
}

matrix_t matrix_inverse(matrix_t* matrix) {
  return matrix_scale(matrix, -1.0f);
}

matrix_t matrix_add(matrix_t* lhs, matrix_t* rhs) {
  matrix_t result;
  for (int i = 0; i < 16; i++) {
    result.elems[i] = lhs->elems[i] + rhs->elems[i];
  }

  return result;
}

matrix_t matrix_sub(matrix_t* lhs, matrix_t* rhs) {
  matrix_t result;
  for (int i = 0; i < 16; i++) {
    result.elems[i] = lhs->elems[i] - rhs->elems[i];
  }

  return result;
}

matrix_t matrix_mul(matrix_t* lhs, matrix_t* rhs) {
  matrix_t result = {};
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      for (int i = 0; i < 4; i++) {
        result.at[x][y] += lhs->at[x][i] * rhs->at[i][y];
      }
    }
  }

  return result;
}

matrix_t matrix_scale(matrix_t* matrix, float scale) {
  matrix_t result;
  for (int i = 0; i < 16; i++) {
    result.elems[i] = matrix->elems[i] * scale;
  }

  return result;
}

point_t matrix_transform_point(matrix_t* matrix, point_t point) {
  point_t result = {};
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      result.at[x] += matrix->at[x][y] * point.at[y];
    }
    result.at[x] += matrix->at[x][3];
  }

  return result;
}

vector_t matrix_transform_vector(matrix_t* matrix, vector_t vector) {
  vector_t result = {};
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      result.at[x] += matrix->at[x][y] * vector.at[y];
    }
  }

  return result;
}
