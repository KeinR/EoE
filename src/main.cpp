#include <iostream>
#include <exception>
#include <memory>
#include <filesystem>

#include "lib/glfw.h"
#include "core/Context.h"
#include "game/Game.h"

#define EXIT_OK 0
#define EXIT_ERR 1


static void glfwErrCallback(int code, const char *desc);

int main(int argc, char **argv) {

    glfwSetErrorCallback(glfwErrCallback);

    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "Failed to init GLFW\n";
        return EXIT_ERR;
    }

    std::shared_ptr<Context> c = std::make_shared<Context>();

    if (!c->getWindow().valid()) {
        std::cerr << "Failed to create GLFW Window\n";
        return EXIT_ERR;
    }

    c->getWindow().makeCurrent();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return EXIT_ERR;
    }

    try {
        namespace fs = std::filesystem;
        fs::current_path(fs::path(argv[0]).parent_path());
        Game game(c);
        game.start();
    } catch (std::exception &e) {
        std::cerr << "Terminted - " << e.what() << '\n';
    }

    // Terminate before GLFW
    c.reset();

    glfwTerminate();

    return EXIT_OK;
}

void glfwErrCallback(int code, const char *desc) {
    std::cerr << "GLFW Error: [0x" << std::hex << code << std::dec << "]: " << desc << '\n';
}

