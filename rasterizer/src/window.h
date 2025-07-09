#pragma once

#include "canvas.h"

bool window_open(const char* title, int width, int height);
void window_close(void);

bool window_is_close_button_pressed(void);

void window_draw_canvas(canvas_t* canvas);
