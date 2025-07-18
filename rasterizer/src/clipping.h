#pragma once

#include "camera.h"
#include "model.h"

typedef struct plane {
  vector3f_t normal;
  float D;
} plane_t;

void fill_clipping_planes(plane_t* clipping_planes, camera_t* camera);

model_t clip_instance(plane_t* clipping_planes, model_t* instance);
