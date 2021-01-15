#include "Context.h"

#include "../lib/glfw.h"
#include "debug.h"

Context::Context():
    viewportWidth(0),
    viewportHeight(0)
{
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    window = std::make_unique<Window>("[no title]", 400, 400);
    window->makeCurrent();

    GLFWwindow *handle = window->getHandle();

    glfwSetInputMode(handle, GLFW_STICKY_KEYS, GLFW_TRUE);
}

bool Context::keyPressed(key k) {
    lockGuard_t g(inputLock);

    keys_t::iterator it = keys.find(k);
    return it != keys.end() && it->second;
}

void Context::useShader(const shader_t &shader) {
    if (usedShader != shader) {
        shader->use();
        usedShader = shader;
    }
}

Context::shader_t Context::getShader() {
    EOE_ASSERT(usedShader);
    return usedShader;
}

Window &Context::getWindow() {
    return *window;
}

int Context::getVPWidth() {
    return viewportWidth;
}

int Context::getVPHeight() {
    return viewportHeight;
}

void Context::setViewport(int width, int height) {
    viewportWidth = width;
    viewportHeight = height;
    glViewport(0, 0, viewportWidth, viewportHeight);
}

void Context::close() {
    window->setShouldClose(true);
}


void Context::processInput() {
    Window::pollEvents();

    lockGuard_t g(inputLock);

    keys[key::ENTER] = window->keyPressed(GLFW_KEY_ENTER);
    keys[key::SPACE] = window->keyPressed(GLFW_KEY_SPACE);
}

