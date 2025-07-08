#include "window.h"

#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

static GLFWwindow* window;
static GLuint texture;

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

  return true;
}

void window_close(void) {
  glDeleteTextures(1, &texture);
  glfwTerminate();
  window = NULL;
}

bool window_is_close_button_pressed(void) {
  glfwPollEvents();
  return glfwWindowShouldClose(window);
}

void window_draw_image(image_t* image) {
  glClear(GL_COLOR_BUFFER_BIT);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    image->width,
    image->height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    image->pixels);

  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-0.5f, -0.5f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-0.5f, 0.5f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(0.5f, -0.5f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-0.5f, 0.5f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(0.5f, 0.5f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(0.5f, -0.5f);
  glEnd();

  glfwSwapBuffers(window);
}
