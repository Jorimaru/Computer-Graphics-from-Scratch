#include "image.h"

#include <stdlib.h>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#define NUM_CHANNELS_PER_PIXEL 4

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

image_t image_read(const char* path) {
  int x, y, channels;
  uint8_t* data = stbi_load(path, &x, &y, &channels, NUM_CHANNELS_PER_PIXEL);

  image_t image = image_create(x, y);
  for (int i = 0; i < x * y; i++) {
    image.pixels[i] = (color_t){
      .r = data[(i * NUM_CHANNELS_PER_PIXEL) + 0],
      .g = data[(i * NUM_CHANNELS_PER_PIXEL) + 1],
      .b = data[(i * NUM_CHANNELS_PER_PIXEL) + 2],
      .a = data[(i * NUM_CHANNELS_PER_PIXEL) + 3],
    };
  }

  stbi_image_free(data);

  return image;
}

void image_write(image_t* image, const char* path) {
  stbi_write_png(
    path,
    image->width,
    image->height,
    4,
    image->pixels,
    image->width * NUM_CHANNELS_PER_PIXEL);
}
