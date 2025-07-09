#pragma once

typedef union point {
  struct {
    float x;
    float y;
    float z;
  };
  float at[3];
} point_t;

typedef union vector {
  struct {
    float x;
    float y;
    float z;
  };
  float at[3];
} vector_t;

typedef union matrix {
  float at[4][4];
  float elems[16];
} matrix_t;

const point_t POINT_ORIGIN = { .x = 0.0f, .y = 0.0f, .z = 0.0f };

const vector_t VECTOR_AXIS_X = { .x = 1.0f, .y = 0.0f, .z = 0.0f };
const vector_t VECTOR_AXIS_Y = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
const vector_t VECTOR_AXIS_Z = { .x = 0.0f, .y = 0.0f, .z = 1.0f };

const matrix_t MATRIX_IDENTITY = {
  .elems = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  }
};

point_t point_add(point_t lhs, vector_t rhs);
point_t point_sub(point_t lhs, vector_t rhs);

float vector_length_squared(vector_t vector);
float vector_length(vector_t vector);
vector_t vector_normalize(vector_t vector);
float vector_dot(vector_t lhs, vector_t rhs);
vector_t vector_cross(vector_t lhs, vector_t rhs);
vector_t vector_invert(vector_t vector);
vector_t vector_add(vector_t lhs, vector_t rhs);
point_t vector_sub(vector_t lhs, vector_t rhs);
vector_t vector_scale(vector_t vector, float scale);

matrix_t matrix_transpose(matrix_t* matrix);
matrix_t matrix_inverse(matrix_t* matrix);
matrix_t matrix_add(matrix_t* lhs, matrix_t* rhs);
matrix_t matrix_sub(matrix_t* lhs, matrix_t* rhs);
matrix_t matrix_mul(matrix_t* lhs, matrix_t* rhs);
matrix_t matrix_scale(matrix_t* matrix, float scale);
point_t matrix_transform_point(matrix_t* matrix, point_t point);
vector_t matrix_transform_vector(matrix_t* matrix, vector_t vector);
