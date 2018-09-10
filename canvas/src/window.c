#include "types.h"

GLFWmonitor* monitor;
static GLFWwindow* window;
static const GLFWvidmode* mode;
int full_screen = 0;

int WindowInit() {
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Load OpenGL */
    gladLoadGL();
    printf("OpenGL %s\n", glGetString(GL_VERSION));

    /* Input callbacks */
    glfwSetKeyCallback(window, key_callback);

    return 1;
}

int WindowActive() {
    int should_close = glfwWindowShouldClose(window);
    return !should_close;
}

void WindowSwap() {
    glfwSwapBuffers(window);
}

void WindowPollEvents() {
    glfwPollEvents();
}

void WindowClose() {
    glfwTerminate();
}
