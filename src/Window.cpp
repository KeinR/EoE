#include "Window.h"

#include "lib/glfw.h"

#include "core/debug.h"

typedef std::unordered_map<GLFWwindow*, WindowEventCallback*> callbacks_t;
static callbacks_t callbacks;

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void cursorPosCallback(GLFWwindow *window, double x, double y);
static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

#define CB_ASSERT(x) EOE_ASSERT(callbacks.count(x) > 0)

Window::Window(const char *title, int width, int height) {
    handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (valid()) {
        // FOR SAFETY
        registerCallback(*this);

        glfwSetKeyCallback(handle, keyCallback);
        glfwSetCursorPosCallback(handle, cursorPosCallback);
        glfwSetMouseButtonCallback(handle, mouseButtonCallback);
    }
}

Window::~Window() {
    deInit();
}

void Window::registerCallback(WindowEventCallback &e) {
    callbacks[handle] = &e;
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

// These should only be called be windows that were creaed by
// this class, so we can make reasonable assumptions as to the
// properties of those windows

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    CB_ASSERT(window);
    callbacks[window]->keyEvent(key, action, mods);
}
void cursorPosCallback(GLFWwindow *window, double x, double y) {
    CB_ASSERT(window);
    callbacks[window]->mouseMoveEvent(
        static_cast<float>(x),
        static_cast<float>(y)
    );
}
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    CB_ASSERT(window);
    callbacks[window]->mouseButtonEvent(button, action, mods);
}




