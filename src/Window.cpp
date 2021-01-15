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

bool Window::keyPressed(int e) {
    return glfwGetKey(handle, e) == GLFW_PRESS;
}

void Window::getMousePos(float &x, float &y) {
    double bx, by;
    glfwGetCursorPos(handle, &bx, &by);
    x = static_cast<float>(bx);
    y = static_cast<float>(by);
}

void Window::getFBSize(int &w, int &h) {
    glfwGetFramebufferSize(handle, &w, &h);
}

int Window::getFBWidth() {
    int w;
    glfwGetFramebufferSize(handle, &w, NULL);
    return w;
}

int Window::getFBHeight() {
    int h;
    glfwGetFramebufferSize(handle, NULL, &h);
    return h;
}

void Window::setSize(int w, int h) {
    glfwSetWindowSize(handle, w, h);
}

void Window::setTitle(const char *str) {
    glfwSetWindowTitle(handle, str);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(handle);
}

void Window::setShouldClose(bool v) {
    glfwSetWindowShouldClose(handle, v);
}


// Static members

void Window::pollEvents() {
    glfwPollEvents();
}

