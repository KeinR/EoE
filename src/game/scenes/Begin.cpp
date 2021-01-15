#include "Begin.h"

#include <iostream>

#include "../Game.h"
#include "../../render/Matrix.h"
#include "../../render/Mesh.h"

#define memb(FUNC) std::bind(&Begin::FUNC, this, std::placeholders::_1)

scn::Begin::Begin(Game &game):
    game(&game),
    proc(game.getContext())
{
}

void scn::Begin::renderNorm(CharRend::renderObj &obj) {
    Game::shader_t &shader = game->getShaders().text;
    Game::font_t &font = game->getFonts().consolas;

    game->getContext().useShader(shader);
    font->bindAtlas();

    Mesh m = font->genMesh(obj.text);
    Matrix mat;
    mat.width = font->getWidth(obj.text);
    mat.height = font->getLinesHeight(obj.text);
    mat.x = obj.x + mat.width / 2.0f;
    mat.y = obj.y + mat.height / 2.0f;
    mat.load(game->getContext());
    m.render();
}

void scn::Begin::script() {
    typedef TextProc prc;
    proc.setCharCooldown(10);
    std::cout << "starting scipt\n";
    // auto f = CharRendF::render_t(std::bind(&Begin::renderNorm, this, std::placeholders::_1));
    proc << memb(renderNorm) << "I really kinda' like cheese for some reason." << prc::enter;
}

void scn::Begin::render() {
    // Thread safe, main thread
    proc.render();
}



