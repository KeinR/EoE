#include "Context.h"

#include "../lib/glfw.h"
#include "debug.h"

Context::Context():
    viewportWidth(0),
    viewportHeight(0),
    mouseX(0),
    mouseY(0),
    leftMousePressed(false)
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


    float x, y;
    window->getMousePos(x, y);
    mouseX.store(x);
    mouseY.store(y);
    window->registerCallback(*this);
}

void Context::keyEvent(int k, int action, int mods) {
    lockGuard_t g(inputLock);
    keys[static_cast<key>(k)] = action != GLFW_RELEASE;
}
void Context::mouseMoveEvent(float x, float y) {
    mouseX.store(x);
    mouseY.store(y);
}
void Context::mouseButtonEvent(int button, int action, int mods) {
    lockGuard_t g(inputLock);
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        leftMousePressed.store(action == GLFW_PRESS);
    }
}

float Context::getMouseX() {
    return mouseX.load();
}

float Context::getMouseY() {
    return mouseY.load();
}

bool Context::isLeftMousePressed() {
    return leftMousePressed.load();
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

