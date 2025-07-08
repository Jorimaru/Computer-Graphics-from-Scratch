#include <stdio.h>

#include "window.h"

int main(void) {
  if (!window_open("Rasterizer", 1280, 720)) {
    return 1;
  }

  while (!window_is_close_button_pressed()) {
    window_swap_buffers();
  }

  window_close();
}
