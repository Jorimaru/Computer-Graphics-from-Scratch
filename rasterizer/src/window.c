#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

static GLFWwindow* window;

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

  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

  return true;
}

void window_close(void) {
  glfwTerminate();
  window = NULL;
}

bool window_is_close_button_pressed(void) {
  glfwPollEvents();
  return glfwWindowShouldClose(window);
}

void window_swap_buffers(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);
}
