#include "Window.h"

#include "lib/glfw.h"

Window::Window(const char *title, int width, int height) {
    handle = glfwCreateWindow(width, height, title, NULL, NULL);
}

Window::~Window() {
    deInit();
}

void Window::deInit() {
    if (handle != nullptr) {
        glfwDestroyWindow(handle);
    }
}

bool Window::valid() {
    return handle != NULL;
}

void Window::show() {
    glfwShowWindow(handle);
}

void Window::hide() {
    glfwHideWindow(handle);
}

GLFWwindow *Window::getHandle() {
    return handle;
}

void Window::makeCurrent() {
    glfwMakeContextCurrent(handle);
}

void Window::swapBuffers() {
    glfwSwapBuffers(handle);
}

void Window::getMousePos(float &x, float &y) {
    double bx, by;
    glfwGetCursorPos(handle, &bx, &by);
    x = static_cast<float>(bx);
    y = static_cast<float>(by);
}

void Window::getSize(int &w, int &h) {
    glfwGetFramebufferSize(handle, &w, &h);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(handle);
}


// Static members

void Window::pollEvents() {
    glfwPollEvents();
}

