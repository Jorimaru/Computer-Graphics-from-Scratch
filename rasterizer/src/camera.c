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
  vector3f_t right = vector3f_cross(camera->forward, camera->up);
  camera->up = vector3f_cross(right, camera->forward);

  vector3f_t forward_projected_onto_yz = vector3f_normalize((vector3f_t){
    .x = 0.0f,
    .y = camera->forward.y,
    .z = camera->forward.z,
  });
  vector3f_t forward_projected_onto_xz = vector3f_normalize((vector3f_t){
    .x = camera->forward.x,
    .y = 0.0f,
    .z = camera->forward.z,
  });
  vector3f_t up_projected_onto_xy = vector3f_normalize((vector3f_t){
    .x = camera->up.x,
    .y = camera->up.y,
    .z = 0.0f,
  });

  float rotation_x = (forward_projected_onto_yz.y < 0.0f ? -1.0f : 1.0f) *
    acosf(vector3f_dot(VECTOR3F_AXIS_Z, forward_projected_onto_yz));
  float rotation_y = (forward_projected_onto_xz.x < 0.0f ? 1.0f : -1.0f) *
    acosf(vector3f_dot(VECTOR3F_AXIS_Z, forward_projected_onto_xz));
  float rotation_z = (up_projected_onto_xy.x < 0.0f ? 1.0f : -1.0f) *
    acosf(vector3f_dot(VECTOR3F_AXIS_Y, up_projected_onto_xy));
  matrix4f_t matrix_rotation =
    rotation_to_matrix(rotation_x, rotation_y, rotation_z);

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
