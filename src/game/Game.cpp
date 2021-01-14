#include "Game.h"

#include "../lib/opengl.h"

Game::Game(const ctx_t &c): c(c) {
}

void Game::start() {
    c->getWindow().show();

    while (!c->getWindow().shouldClose()) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        c->getWindow().swapBuffers();
        Window::pollEvents();
    }
}

