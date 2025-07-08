#pragma once

#include <stdint.h>

typedef struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} color_t;

color_t color_scale(color_t color, float scale);
color_t color_add(color_t lhs, color_t rhs);
color_t color_clamp(color_t color);
