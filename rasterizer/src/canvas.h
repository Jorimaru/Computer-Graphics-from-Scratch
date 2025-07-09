#pragma once

#include "color.h"
#include "image.h"

typedef struct canvas {
  int width;
  int height;
  color_t* pixels;
} canvas_t;

canvas_t canvas_create(int width, int height);
void canvas_destroy(canvas_t* canvas);

image_t canvas_as_image(canvas_t* canvas);

void canvas_clear(canvas_t* canvas, color_t color);
void canvas_set_pixel(canvas_t* canvas, int x, int y, color_t color);
