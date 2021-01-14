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
    font = std::make_shared<Font>("data/fonts/consolas18.bff");
}

void Game::start() {
    c->getWindow().makeCurrent();
    c->getWindow().show();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    Textbox box(*c, font);
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(*c,
        "data/shaders/text.vert",
        "data/shaders/text.frag"
    );
    c->useShader(shader);
    shader->set1i("atlas", 0);
    shader->set4f("color", 0, 1, 0, 1);
    box.pushFunc(std::make_shared<CharRendF>(
        [&shader](Context &c)->void{
            c.useShader(shader);
        },
        [](const CharRendF::renderObj &obj)->void{
            obj.font->bindAtlas();
            Mesh m = obj.font->genMesh(obj.word);
            Matrix mat;
            mat.x = obj.cx;
            mat.y = obj.cy;
            mat.width = obj.width;
            mat.height = obj.height;
            mat.load(*obj.c);
            m.render();
        }
    ));
    std::string word = "foo";
    for (char c : word) {
        box.pushChar(c);
    }

    while (!c->getWindow().shouldClose()) {
        c->setViewport(400, 400);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        box.render();

        c->getWindow().swapBuffers();
        Window::pollEvents();
    }
}

