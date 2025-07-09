#include "canvas.h"

#include <stdlib.h>

canvas_t canvas_create(int width, int height) {
  return (canvas_t){
    .width = width,
    .height = height,
    .pixels = calloc(width * height, sizeof(color_t)),
  };
}

void canvas_destroy(canvas_t* canvas) {
  free(canvas->pixels);
  *canvas = (canvas_t){};
}

image_t canvas_as_image(canvas_t* canvas) {
  return (image_t){
    .width = canvas->width,
    .height = canvas->height,
    .pixels = canvas->pixels,
  };
}

void canvas_clear(canvas_t* canvas, color_t color) {
  for (int i = 0; i < (canvas->width * canvas->height); i++) {
    canvas->pixels[i] = color;
  }
}

void canvas_set_pixel(canvas_t* canvas, int x, int y, color_t color) {
  int index_x = (canvas->width / 2) + x;
  int index_y = (canvas->height / 2) + y;
  canvas->pixels[index_x + (index_y * canvas->width)] = color;
}
