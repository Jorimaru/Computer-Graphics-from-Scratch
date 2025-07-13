#include "scene.h"

#include <stdlib.h>

#include "renderer.h"

static void render_instance(canvas_t* canvas,
                            camera_t* camera,
                            matrix4f_t* matrix_projection_view,
                            instance_t* instance) {
  matrix4f_t matrix_transform = transform_to_matrix(&instance->transform);
  matrix4f_t matrix_view_transform =
    matrix4f_mul(matrix_projection_view, &matrix_transform);
  point3f_t* transformed_vertices =
    (point3f_t*)malloc(sizeof(point3f_t) * instance->model->num_vertices);
  for (int i = 0; i < instance->model->num_vertices; i++) {
    transformed_vertices[i] = matrix4f_transform_point3f(
      &matrix_view_transform,
      instance->model->vertices[i]);
  }
  render_object(
    canvas,
    camera,
    transformed_vertices,
    instance->model->num_vertices,
    instance->model->triangles,
    instance->model->num_triangles);
  free(transformed_vertices);
}

void render_scene(canvas_t* canvas, scene_t* scene) {
  matrix4f_t matrix_projection_view =
    camera_projection_view_matrix(&scene->camera);
  for (int i = 0; i < scene->num_instances; i++) {
    render_instance(
      canvas,
      &scene->camera,
      &matrix_projection_view,
      &scene->instances[i]);
  }
}
