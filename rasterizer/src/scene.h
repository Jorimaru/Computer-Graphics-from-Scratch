#pragma once

#include "camera.h"
#include "model.h"
#include "transform.h"

typedef struct instance {
  model_t* model;
  transform_t transform;
} instance_t;

typedef struct scene {
  camera_t camera;
  instance_t* instances;
  int num_instances;
} scene_t;

void render_scene(canvas_t* canvas, scene_t* scene);
