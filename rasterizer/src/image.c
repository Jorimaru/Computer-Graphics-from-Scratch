#include "image.h"

#include <stdlib.h>

image_t image_create(int width, int height) {
  return (image_t){
    .width = width,
    .height = height,
    .pixels = (color_t*)calloc(width * height, sizeof(color_t)),
  };
}

void image_destroy(image_t* image) {
  free(image->pixels);
  *image = (image_t){};
}

void image_set_pixel(image_t* image, int x, int y, color_t color) {
  image->pixels[x + (y * image->width)] = color;
}

color_t image_get_pixel(image_t* image, int x, int y) {
  return image->pixels[x + (y * image->width)];
}
