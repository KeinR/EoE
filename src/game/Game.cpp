#include "Game.h"

#include <iostream>

#include "../lib/opengl.h"

#include "../Textbox.h"
#include "../TextProc.h"
#include "../CharRendF.h"
#include "../render/Shader.h"
#include "../render/Mesh.h"
#include "../render/Matrix.h"
#include "../core/error.h"
#include "scenes/Begin.h"

Game::Game(const ctx_t &c): c(c) {
    fonts.consolas = std::make_shared<Font>("data/fonts/consolas18.bff");
    shaders.text = std::make_shared<Shader>(*c,
        "data/shaders/text.vert",
        "data/shaders/text.frag"
    );

    c->useShader(shaders.text);
    shaders.text->set1i("atlas", 0);
    shaders.text->set4f("color", 0, 1, 0, 1);

}

void Game::setScene(const scene_t &scn) {
    lockGuard_t g(sceneLock);
    nextScene = scn;
}

void Game::syncScene() {
    lockGuard_t g(sceneLock);
    if (nextScene) {
        scene = nextScene;
        nextScene.reset();
    }
}

void Game::script() {
    std::shared_ptr<scn::Begin> begin = std::make_shared<scn::Begin>(*this);
    setScene(begin);
    begin->script();
}

Context &Game::getContext() {
    return *c;
}

Game::fonts_t &Game::getFonts() {
    return fonts;
}

Game::shaders_t &Game::getShaders() {
    return shaders;
}

void Game::start() {
    c->getWindow().makeCurrent();
    c->getWindow().show();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    beginScript();

    while (!c->getWindow().shouldClose()) {
        c->setViewport(400, 400);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        syncScene();
        if (scene) {
            scene->render();
        }

        c->getWindow().swapBuffers();
        c->processInput();
    }

    joinScript();
}

