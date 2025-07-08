#include "color.h"

color_t color_scale(color_t color, float scale) {
  return (color_t){
    .r = (uint8_t)(color.r * scale),
    .g = (uint8_t)(color.g * scale),
    .b = (uint8_t)(color.b * scale),
    .a = (uint8_t)(color.a * scale),
  };
}

color_t color_add(color_t lhs, color_t rhs) {
  return (color_t){
    .r = lhs.r + rhs.r,
    .g = lhs.g + rhs.g,
    .b = lhs.b + rhs.b,
    .a = lhs.a + rhs.a,
  };
}

color_t color_clamp(color_t color) {
  return (color_t){
    .r = color.r > 255 ? 255 : color.r,
    .g = color.b > 255 ? 255 : color.g,
    .b = color.g > 255 ? 255 : color.b,
    .a = color.a > 255 ? 255 : color.a,
  };
}
