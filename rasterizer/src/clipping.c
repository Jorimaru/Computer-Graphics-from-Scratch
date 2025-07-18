#include "clipping.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "linear_algebra.h"

typedef struct sphere {
  point3f_t center;
  float radius;
} sphere_t;

void fill_clipping_planes(plane_t* clipping_planes, camera_t* camera) {
  vector3f_t viewport_right = {
    .x = camera->viewport_width / 2.0f,
    .y = 0.0f,
    .z = camera->viewport_distance,
  };
  vector3f_t viewport_left = {
    .x = -camera->viewport_width / 2.0f,
    .y = 0.0f,
    .z = camera->viewport_distance,
  };
  vector3f_t viewport_top = {
    .x = 0.0f,
    .y = camera->viewport_height / 2.0f,
    .z = camera->viewport_distance,
  };
  vector3f_t viewport_bottom = {
    .x = 0.0f,
    .y = -camera->viewport_height / 2.0f,
    .z = camera->viewport_distance,
  };

  clipping_planes[0] = (plane_t){
    .normal = VECTOR3F_AXIS_Z,
    .D = -camera->viewport_distance,
  };
  clipping_planes[1] = (plane_t){
    .normal =
      vector3f_normalize(vector3f_cross(viewport_right, VECTOR3F_AXIS_Y)),
    .D = 0.0f,
  };
  clipping_planes[2] = (plane_t){
    .normal =
      vector3f_normalize(vector3f_cross(VECTOR3F_AXIS_Y, viewport_left)),
    .D = 0.0f,
  };
  clipping_planes[3] = (plane_t){
    .normal =
      vector3f_normalize(vector3f_cross(VECTOR3F_AXIS_X, viewport_top)),
    .D = 0.0f,
  };
  clipping_planes[4] = (plane_t){
    .normal =
      vector3f_normalize(vector3f_cross(viewport_bottom, VECTOR3F_AXIS_X)),
    .D = 0.0f,
  };
}

static sphere_t model_bounding_sphere(model_t* model) {
  float sum[3] = {};
  for (int i = 0; i < model->num_vertices; i++) {
    for (int j = 0; j < 3; j++) {
      sum[j] += model->vertices[i].at[j];
    }
  }

  point3f_t center;
  for (int i = 0; i < 3; i++) {
    center.at[i] = sum[i] / model->num_vertices;
  }

  float max_distance_squared = 0.0f;
  for (int i = 0; i < model->num_vertices; i++) {
    float distance_squared =
      point3f_distance_squared(center, model->vertices[i]);
    if (distance_squared > max_distance_squared) {
      max_distance_squared = distance_squared;
    }
  }

  return (sphere_t){
    .center = center,
    .radius = sqrtf(max_distance_squared),
  };
}

static float plane_signed_distance_to_point(plane_t* plane, point3f_t p) {
  return (plane->normal.x * p.x) +
         (plane->normal.y * p.y) +
         (plane->normal.z * p.z) +
         plane->D;
}

static int model_add_vertex(model_t* model, point3f_t vertex) {
  model->vertices = (point3f_t*)realloc(
    model->vertices,
    sizeof(point3f_t) * (model->num_vertices + 1));
  model->vertices[model->num_vertices] = vertex;

  return model->num_vertices++;
}

static void model_add_triangle(model_t* model,
                               triangle_t* triangle,
                               int max_num_triangles) {
  if (model->num_triangles >= max_num_triangles) {
    model->triangles = (triangle_t*)realloc(
      model->triangles,
      sizeof(triangle_t) * (model->num_triangles + 1));
  }
  model->triangles[model->num_triangles++] = *triangle;
}

static point3f_t plane_intersect(plane_t* plane, point3f_t p0, point3f_t p1) {
  vector3f_t v0 = point3f_to_vector3f(p0);

  float t =
    (-plane->D - vector3f_dot(plane->normal, v0)) /
    vector3f_dot(plane->normal, point3f_sub_point3f(p1, p0));

  return point3f_add(p0, vector3f_scale(point3f_sub_point3f(p1, p0), t));
}

static void model_add_new_triangle_from_1_point(model_t* model,
                                                int i0,
                                                int i1,
                                                int i2,
                                                color_t color,
                                                int max_num_triangles,
                                                plane_t* clipping_plane) {
  point3f_t v0 = model->vertices[i0];
  point3f_t v1 = model->vertices[i1];
  point3f_t v2 = model->vertices[i2];

  point3f_t v1_prime = plane_intersect(clipping_plane, v0, v1);
  point3f_t v2_prime = plane_intersect(clipping_plane, v0, v2);

  int i1_prime = model_add_vertex(model, v1_prime);
  int i2_prime = model_add_vertex(model, v2_prime);

  triangle_t new_triangle = {
    .indices = { i0, i1_prime, i2_prime },
    .color = color,
  };
  model_add_triangle(model, &new_triangle, max_num_triangles);
}

static void model_add_new_triangle_from_2_points(model_t* model,
                                                 int i0,
                                                 int i1,
                                                 int i2,
                                                 color_t color,
                                                 int max_num_triangles,
                                                 plane_t* clipping_plane) {
  point3f_t v0 = model->vertices[i0];
  point3f_t v1 = model->vertices[i1];
  point3f_t v2 = model->vertices[i2];

  point3f_t v0_prime = plane_intersect(clipping_plane, v0, v2);
  point3f_t v1_prime = plane_intersect(clipping_plane, v1, v2);

  int i0_prime = model_add_vertex(model, v0_prime);
  int i1_prime = model_add_vertex(model, v1_prime);

  triangle_t new_triangle1 = {
    .indices = { i0, i1, i0_prime },
    .color = color,
  };
  model_add_triangle(model, &new_triangle1, max_num_triangles);

  triangle_t new_triangle2 = {
    .indices = { i1, i1_prime, i0_prime },
    .color = color,
  };
  model_add_triangle(model, &new_triangle2, max_num_triangles);
}

static model_t clip_instance_with_plane(plane_t* clipping_plane,
                                        model_t* instance,
                                        sphere_t* bounding_sphere) {
  float signed_distance =
    plane_signed_distance_to_point(clipping_plane, bounding_sphere->center);
  if (fabsf(signed_distance) > bounding_sphere->radius) {
    if (signed_distance > 0.0f) {
      model_t copy = {
        .vertices =
          (point3f_t*)malloc(sizeof(point3f_t) * instance->num_vertices),
        .triangles =
          (triangle_t*)malloc(sizeof(triangle_t) * instance->num_triangles),
        .num_vertices = instance->num_vertices,
        .num_triangles = instance->num_triangles,
      };
      memcpy(
        copy.vertices,
        instance->vertices,
        sizeof(point3f_t) * copy.num_vertices);
      memcpy(
        copy.triangles,
        instance->triangles,
        sizeof(triangle_t) * copy.num_triangles);

      return copy;
    } else {
      return (model_t){};
    }
  }
  
  model_t clipped_instance = {
    .vertices = (point3f_t*)malloc(sizeof(point3f_t) * instance->num_vertices),
    .triangles =
      (triangle_t*)malloc(sizeof(triangle_t) * instance->num_triangles),
    .num_vertices = instance->num_vertices,
    .num_triangles = 0,
  };
  memcpy(
    clipped_instance.vertices,
    instance->vertices,
    sizeof(point3f_t) * clipped_instance.num_vertices);

  for (int i = 0; i < instance->num_triangles; i++) {
    triangle_t triangle = instance->triangles[i];

    int accepted_indices[3];
    int rejected_indices[3];
    int num_accepted_indices = 0;
    for (int j = 0; j < 3; j++) {
      float vertex_signed_distance = plane_signed_distance_to_point(
        clipping_plane,
        instance->vertices[triangle.indices[j]]);
      if (vertex_signed_distance >= 0.0f) {
        accepted_indices[num_accepted_indices++] = triangle.indices[j];
      } else {
        rejected_indices[j - num_accepted_indices] = triangle.indices[j];
      }
    }

    switch (num_accepted_indices) {
      case 3:
        model_add_triangle(
          &clipped_instance,
          &triangle,
          instance->num_triangles);
        break;
      case 2:
        model_add_new_triangle_from_2_points(
          &clipped_instance,
          accepted_indices[0],
          accepted_indices[1],
          rejected_indices[0],
          triangle.color,
          instance->num_triangles,
          clipping_plane);
        break;
      case 1:
        model_add_new_triangle_from_1_point(
          &clipped_instance,
          accepted_indices[0],
          rejected_indices[0],
          rejected_indices[1],
          triangle.color,
          instance->num_triangles,
          clipping_plane);
        break;
    }
  }

  return clipped_instance;
}

model_t clip_instance(plane_t* clipping_planes, model_t* instance) {
  sphere_t bounding_sphere = model_bounding_sphere(instance);

  model_t clipped_instance = *instance;
  for (int i = 0; i < 5; i++) {
    model_t new_clipped_instance = clip_instance_with_plane(
      &clipping_planes[i],
      &clipped_instance,
      &bounding_sphere);
    if (i > 0) {
      free(clipped_instance.vertices);
      free(clipped_instance.triangles);
    }
    clipped_instance = new_clipped_instance;
  }

  return clipped_instance;
}
