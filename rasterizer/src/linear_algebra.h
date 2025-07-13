#pragma once

typedef union point2i {
  struct {
    int x;
    int y;
  };
  int at[2];
} point2i_t;

typedef union vector2i {
  struct {
    int x;
    int y;
  };
  int at[2];
} vector2i_t;

typedef union point3f {
  struct {
    float x;
    float y;
    float z;
  };
  float at[3];
} point3f_t;

typedef union vector3f {
  struct {
    float x;
    float y;
    float z;
  };
  float at[3];
} vector3f_t;

typedef union matrix4f {
  float at[4][4];
  float elems[16];
} matrix4f_t;

static const point2i_t POINT2I_ORIGIN = { .x = 0, .y = 0 };

static const vector2i_t VECTOR2I_AXIS_X = { .x = 1, .y = 0 };
static const vector2i_t VECTOR2I_AXIS_Y = { .x = 0, .y = 1 };

static const point3f_t POINT3F_ORIGIN = { .x = 0.0f, .y = 0.0f, .z = 0.0f };

static const vector3f_t VECTOR3F_AXIS_X = { .x = 1.0f, .y = 0.0f, .z = 0.0f };
static const vector3f_t VECTOR3F_AXIS_Y = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
static const vector3f_t VECTOR3F_AXIS_Z = { .x = 0.0f, .y = 0.0f, .z = 1.0f };

static const matrix4f_t MATRIX4F_IDENTITY = {
  .elems = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  }
};

point2i_t point2i_add(point2i_t lhs, vector2i_t rhs);
point2i_t point2i_sub(point2i_t lhs, vector2i_t rhs);
vector2i_t point2i_sub_point2i(point2i_t lhs, point2i_t rhs);

vector2i_t vector2i_invert(vector2i_t vector);
vector2i_t vector2i_add(vector2i_t lhs, vector2i_t rhs);
vector2i_t vector2i_sub(vector2i_t lhs, vector2i_t rhs);

point3f_t point3f_add(point3f_t lhs, vector3f_t rhs);
point3f_t point3f_sub(point3f_t lhs, vector3f_t rhs);
vector3f_t point3f_sub_point3f(point3f_t lhs, point3f_t rhs);
point3f_t point3f_scale(point3f_t point, float scale);

float vector3f_length_squared(vector3f_t vector);
float vector3f_length(vector3f_t vector);
vector3f_t vector3f_normalize(vector3f_t vector);
float vector3f_dot(vector3f_t lhs, vector3f_t rhs);
vector3f_t vector3f_cross(vector3f_t lhs, vector3f_t rhs);
vector3f_t vector3f_invert(vector3f_t vector);
vector3f_t vector3f_add(vector3f_t lhs, vector3f_t rhs);
vector3f_t vector3f_sub(vector3f_t lhs, vector3f_t rhs);
vector3f_t vector3f_scale(vector3f_t vector, float scale);

matrix4f_t matrix4f_transpose(matrix4f_t* matrix);
matrix4f_t matrix4f_inverse(matrix4f_t* matrix);
matrix4f_t matrix4f_add(matrix4f_t* lhs, matrix4f_t* rhs);
matrix4f_t matrix4f_sub(matrix4f_t* lhs, matrix4f_t* rhs);
matrix4f_t matrix4f_mul(matrix4f_t* lhs, matrix4f_t* rhs);
matrix4f_t matrix4f_scale(matrix4f_t* matrix, float scale);
point3f_t matrix4f_transform_point3f(matrix4f_t* matrix, point3f_t point);
vector3f_t matrix4f_transform_vector3f(matrix4f_t* matrix, vector3f_t vector);
