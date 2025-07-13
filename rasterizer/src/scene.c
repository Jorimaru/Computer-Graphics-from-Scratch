#include "scene.h"

#include <stdlib.h>

#include "renderer.h"

static point3f_t* transform_instance(instance_t* instance,
                                     matrix4f_t* projection_view_matrix) {
  matrix4f_t transform_matrix = transform_to_matrix(&instance->transform);
  matrix4f_t projection_view_transform_matrix =
    matrix4f_mul(projection_view_matrix, &transform_matrix);
  
  point3f_t* transformed_vertices =
    (point3f_t*)malloc(sizeof(point3f_t) * instance->model->num_vertices);
  for (int i = 0; i < instance->model->num_vertices; i++) {
    transformed_vertices[i] = matrix4f_transform_point3f(
      &projection_view_transform_matrix,
      instance->model->vertices[i]);
  }

  return transformed_vertices;
}

void render_scene(canvas_t* canvas, scene_t* scene) {
  matrix4f_t projection_view_matrix =
    camera_projection_view_matrix(&scene->camera);
  for (int i = 0; i < scene->num_instances; i++) {
    point3f_t* transformed_vertices =
      transform_instance(&scene->instances[i], &projection_view_matrix);
    point2i_t* projected_vertices = project_vertices(
      &scene->camera,
      canvas,
      transformed_vertices,
      scene->instances[i].model->num_vertices);
    render_triangles(
      canvas,
      scene->instances[i].model->triangles,
      scene->instances[i].model->num_triangles,
      projected_vertices);
  }
}
