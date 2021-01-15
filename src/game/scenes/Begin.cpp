#include "Begin.h"

#include <iostream>

#include "../Game.h"
#include "../../render/Matrix.h"
#include "../../render/Mesh.h"

#define memb(FUNC) std::bind(&Begin::FUNC, this, std::placeholders::_1)

scn::Begin::Begin(Game &game):
    game(&game),
    proc(game, game.getContext())
{
    proc.getTextbox()->setWrappingWidth(game.getContext().getWindow().getFBWidth());
}

void scn::Begin::renderNorm(CharRend::renderObj &obj) {
    Game::shader_t &shader = game->getShaders().text;
    Game::font_t &font = game->getFonts().consolas;

    game->getContext().useShader(shader);
    font->bindAtlas();

    shader->set4f("color", 0.7, 0.7, 0.7, 1);

    Font::wrapResult wrap = font->wrapText(obj.text, obj.wrapWidth, 0, obj.x, obj.y);

    Mesh m = font->genMesh(wrap.text, obj.x, 0);
    Matrix mat;
    mat.width = wrap.width;
    mat.height = wrap.height;
    mat.x = wrap.cx;
    mat.y = wrap.cy;
    mat.load(game->getContext());
    m.render();

    obj.x = wrap.x;
    obj.y = wrap.y;

}

void scn::Begin::script() {
    typedef TextProc prc;
    proc.setCharCooldown(50);
    proc << memb(renderNorm) << "I really kinda' like cheese for some reason.\\\nThere's just something about it..." << prc::input;
}

void scn::Begin::render() {
    // Thread safe, main thread
    proc.render();
}



