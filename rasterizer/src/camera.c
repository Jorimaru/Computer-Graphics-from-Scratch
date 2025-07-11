#include "camera.h"

point2i_t viewport_to_canvas(camera_t* camera, canvas_t* canvas, point3f_t p) {
  return (point2i_t){
    .x = p.x * (canvas->width / camera->width),
    .y = p.y * (canvas->height / camera->height),
  };
}

point2i_t project_vertex(camera_t* camera, canvas_t* canvas, point3f_t p) {
  return viewport_to_canvas(camera, canvas, (point3f_t){
    .x = (p.x * camera->d) / p.z,
    .y = (p.y * camera->d) / p.z,
    .z = camera->d,
  });
}
