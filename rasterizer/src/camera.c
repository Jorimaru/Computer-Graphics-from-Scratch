#include "camera.h"

#include <math.h>
#include <stdlib.h>

#include "transform.h"

point2i_t viewport_to_canvas(camera_t* camera, canvas_t* canvas, point3f_t p) {
  return (point2i_t){
    .x = p.x * (canvas->width / camera->viewport_width),
    .y = p.y * (canvas->height / camera->viewport_height),
  };
}

point2i_t* project_vertices(camera_t* camera,
                            canvas_t* canvas,
                            point3f_t* vertices,
                            int num_vertices) {
  point2i_t* projected_vertices =
    (point2i_t*)malloc(sizeof(point2i_t) * num_vertices);
  for (int i = 0; i < num_vertices; i++) {
    projected_vertices[i] = viewport_to_canvas(camera, canvas, vertices[i]);
  }

  return projected_vertices;
}

matrix4f_t camera_projection_matrix(camera_t* camera) {
  return (matrix4f_t){
    .elems = {
      camera->viewport_distance, 0.0f, 0.0f, 0.0f,
      0.0f, camera->viewport_distance, 0.0f, 0.0f,
      0.0f, 0.0f, camera->viewport_distance, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
    },
  };
}

matrix4f_t camera_view_matrix(camera_t* camera) {
  vector3f_t right = vector3f_cross(camera->up, camera->forward);
  camera->up = vector3f_cross(camera->forward, right);

  matrix4f_t matrix_rotation = {
    .elems = {
      right.x, right.y, right.z, 0.0f,
      camera->up.x, camera->up.y, camera->up.z, 0.0f,
      camera->forward.x, camera->forward.y, camera->forward.z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    },
  };

  matrix4f_t matrix_translation = translation_to_matrix(
    -camera->position.x,
    -camera->position.y,
    -camera->position.z);
  return matrix4f_mul(&matrix_rotation, &matrix_translation);
}

matrix4f_t camera_projection_view_matrix(camera_t* camera) {
  matrix4f_t matrix_projection = camera_projection_matrix(camera);
  matrix4f_t matrix_view = camera_view_matrix(camera);

  return matrix4f_mul(&matrix_projection, &matrix_view);
}

void camera_rotate(camera_t* camera, float x, float y, float z) {
  matrix4f_t rotation_matrix = rotation_to_matrix(x, y, z);

  camera->forward =
    matrix4f_transform_vector3f(&rotation_matrix, camera->forward);
  camera->up = matrix4f_transform_vector3f(&rotation_matrix, camera->up);
}

void camera_move_forward(camera_t* camera, float speed) {
  vector3f_t move_forward = vector3f_scale(camera->forward, speed);

  camera->position = point3f_add(camera->position, move_forward);
}

void camera_move_up(camera_t* camera, float speed) {
  vector3f_t move_up = vector3f_scale(camera->up, speed);

  camera->position = point3f_add(camera->position, move_up);
}

void camera_move_right(camera_t* camera, float speed) {
  vector3f_t right = vector3f_cross(camera->up, camera->forward);
  vector3f_t move_right = vector3f_scale(right, speed);

  camera->position = point3f_add(camera->position, move_right);
}
