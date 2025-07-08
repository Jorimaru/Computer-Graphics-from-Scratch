#include <stdio.h>

#include "image.h"
#include "window.h"

int main(void) {
  if (!window_open("Rasterizer", 1280, 720)) {
    return 1;
  }

  image_t canvas = image_create(1280, 720);
  for (int x = 0; x < canvas.width; x++) {
    for (int y = 0; y < canvas.height; y++) {
      image_set_pixel(&canvas, x, y, (color_t){
        .r = (uint8_t)(((float)x / (float)canvas.width) * 255),
        .g = (uint8_t)(((float)y / (float)canvas.height) * 255),
        .b = 0,
        .a = 255
      });
    }
  }
  while (!window_is_close_button_pressed()) {
    window_draw_image(&canvas);
  }

  image_destroy(&canvas);
  window_close();
}
