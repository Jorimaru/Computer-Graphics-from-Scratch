#include "window.h"
#include "input.h"

#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

static GLFWwindow* window;
static GLuint texture;
static bool locked;
static double current_cursor_x;
static double current_cursor_y;
static double previous_cursor_x;
static double previous_cursor_y;

bool window_open(const char* title, int width, int height) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to init GLFW\n");
    return false;
  }

  window = glfwCreateWindow(width, height, title, 0, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create window\n");
    return false;
  }

  glfwMakeContextCurrent(window);

  glEnable(GL_TEXTURE_2D);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  locked = false;

  glfwGetCursorPos(window, &current_cursor_x, &current_cursor_y);
  previous_cursor_x = current_cursor_x;
  previous_cursor_y = current_cursor_y;

  return true;
}

void window_close(void) {
  glDeleteTextures(1, &texture);
  glfwTerminate();
  window = NULL;
}

bool window_is_close_button_pressed(void) {
  glfwPollEvents();
  
  previous_cursor_x = current_cursor_x;
  previous_cursor_y = current_cursor_y;
  glfwGetCursorPos(window, &current_cursor_x, &current_cursor_y);

  if (locked && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    locked = false;
  } else if (!locked &&
             glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    if (!(current_cursor_x < 0 ||
          current_cursor_x > width ||
          current_cursor_y < 0 ||
          current_cursor_y > height)) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      locked = true;
    }
  }

  return glfwWindowShouldClose(window);
}

void window_draw_canvas(canvas_t* canvas) {
  glClear(GL_COLOR_BUFFER_BIT);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    canvas->width,
    canvas->height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    canvas->pixels);

  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(1.0f, -1.0f);
  glEnd();

  glfwSwapBuffers(window);
}

bool move_up(void) {
  return glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
}

bool move_down(void) {
  return glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;
}

bool move_left(void) {
  return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
}

bool move_right(void) {
  return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}

bool move_forward(void) {
  return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
}

bool move_backward(void) {
  return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
}

float rotate_vertically(void) {
  return locked * (float)(current_cursor_y - previous_cursor_y);
}

float rotate_horizontally(void) {
  return locked * (float)(current_cursor_x - previous_cursor_x);
}
