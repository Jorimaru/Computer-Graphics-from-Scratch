#pragma once

#include "color.h"

typedef struct image {
  int width;
  int height;
  color_t* pixels;
} image_t;

image_t image_create(int width, int height);
void image_destroy(image_t* image);

void image_set_pixel(image_t* image, int x, int y, color_t color);
color_t image_get_pixel(image_t* image, int x, int y);
