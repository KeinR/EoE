#include "Game.h"

#include <iostream>

#include "../lib/opengl.h"

#include "../Textbox.h"
#include "../CharRendF.h"
#include "../render/Shader.h"
#include "../render/Mesh.h"
#include "../render/Matrix.h"
#include "../core/error.h"

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

void Game::start() {
    c->getWindow().makeCurrent();
    c->getWindow().show();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    Textbox box(*c);
    box.pushFunc([this](const CharRendF::renderObj &obj)->void{
        c->useShader(shaders.text);
        auto &font = fonts.consolas;
        font->bindAtlas();
        Mesh m = font->genMesh(obj.text);
        Matrix mat;
        mat.width = font->getWidth(obj.text);
        mat.height = font->getLinesHeight(obj.text);
        mat.x = obj.x + mat.width / 2.0f;
        mat.y = obj.y + mat.height / 2.0f;
        mat.load(*obj.c);
        m.render();
    });
    box.pushString("foo");

    while (!c->getWindow().shouldClose()) {
        c->setViewport(400, 400);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        box.render();

        c->getWindow().swapBuffers();
        Window::pollEvents();
    }
}

