#include "Begin.h"

#include <iostream>

#include "../Game.h"
#include "../../render/Matrix.h"
#include "../../render/Mesh.h"

// #define memb(FUNC) std::bind(&Begin::FUNC, this, std::placeholders::_1)

scn::Begin::Begin(Game &game):
    game(&game),
    proc(game, game.getContext())
{
    proc.getTextbox()->setWrappingWidth(game.getContext().getWindow().getFBWidth());
}

void scn::Begin::renderNorm(CharRend::renderObj &obj) {
    Game::font_t &font = game->getFonts().consolas;

    font->bindAtlas();

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
    typedef CharRendF::render_t func_t;
    proc.setCharCooldown(50);

    Game::shader_t &shader = game->getShaders().text;
    Context &c = game->getContext();

    // TODO: Find a way of doing this that isn't so moronic
#define COLOR(RED, GREEN, BLUE, ALPHA)\
    [this, &shader, &c](CharRend::renderObj &obj)->void{\
        c.useShader(shader);\
        shader->set4f("color", RED, BLUE, GREEN, ALPHA);\
        this->renderNorm(obj);\
    };

    func_t white = COLOR(0.8, 0.8, 0.8, 1);
    func_t red = COLOR(1, 0.2, 0.2, 1);

    proc << white << "There was once a time when " << red << "GIANTS" << white <<
    "\\ ruled the land.\nAnd it was not all that great..." << prc::input;
}

void scn::Begin::render() {
    // Thread safe, main thread
    proc.render();
}



