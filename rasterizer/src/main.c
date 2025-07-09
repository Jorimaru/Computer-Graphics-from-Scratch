#include <stdio.h>

#include "image.h"
#include "window.h"

int main(void) {
  if (!window_open("Rasterizer", 1280, 720)) {
    return 1;
  }

  image_t image = image_create(1280, 720);
  for (int x = 0; x < image.width; x++) {
    for (int y = 0; y < image.height; y++) {
      image_set_pixel(&image, x, y, (color_t){
        .r = (uint8_t)(((float)x / (float)image.width) * 255),
        .g = (uint8_t)(((float)y / (float)image.height) * 255),
        .b = 0,
        .a = 255
      });
    }
  }

  image_write(&image, "test.png");
  image_t canvas = image_read("test.png");

  while (!window_is_close_button_pressed()) {
    window_draw_image(&canvas);
  }

  image_destroy(&canvas);
  window_close();
}
