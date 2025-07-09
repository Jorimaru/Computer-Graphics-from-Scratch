#pragma once

#include <stdint.h>

typedef struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} color_t;

static const color_t COLOR_BLACK = { .r = 0, .g = 0, .b = 0, .a = 255 };
static const color_t COLOR_WHITE = { .r = 255, .g = 255, .b = 255, .a = 255 };

color_t color_scale(color_t color, float scale);
color_t color_add(color_t lhs, color_t rhs);
color_t color_clamp(color_t color);
