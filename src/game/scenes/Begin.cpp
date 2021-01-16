#include "Begin.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../Game.h"
#include "../../render/Matrix.h"
#include "../../render/Mesh.h"

class Option {
public:
    typedef std::function<void()> callback_t;
    typedef std::shared_ptr<Textbox> textbox_t;
private:
    std::vector<std::pair<key, callback_t>> choices;
    std::stringstream text;
    Context *c;
    textbox_t textbox;
public:
    Option(Context &c, const textbox_t &tb);
    void add(const std::string &str, const callback_t &cb);
    void clear();
    void run();
};

Option::Option(Context &c, const textbox_t &tb):
    c(&c), textbox(tb) {
}

void Option::add(const std::string &str, const callback_t &cb) {
    std::size_t num = choices.size() + 1;
    if (num > 9) {
        throw std::invalid_argument("Too many options");
    }
    choices.emplace_back(keyUtil::mapIntToKey(num), cb);
    text << "    [" << num << "] " << str << '\n';
}

void Option::clear() {
    choices.clear();
}

void Option::run() {
    textbox->pushChar('\n');
    textbox->pushChar('\n');

    textbox->pushString(text.str());
    bool done = false;
    callback_t *func;
    while (!done) {
        for (std::pair<key, callback_t> &p : choices) {
            if (c->keyPressed(p.first)) {
                done = true;
                func = &p.second;
                break;
            }
        }
    }

    textbox->pushChar('\n');

    (*func)();
}


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
    typedef TextProc::command com;
    typedef CharRendF::render_t func_t;
    typedef Textbox::event_t event_t;
    proc.setCharCooldown(50);

    Game::shader_t &shader = game->getShaders().text;
    Context &c = game->getContext();

#define memb(FUNC) std::bind(&Begin::FUNC, this, std::placeholders::_1)

    // TODO: Find a way of doing this that isn't so moronic
#define COLOR(RED, GREEN, BLUE, ALPHA)\
    [&shader, &c]()->void{\
        c.useShader(shader);\
        shader->set4f("color", RED, BLUE, GREEN, ALPHA);\
    };

    event_t white = COLOR(0.8, 0.8, 0.8, 1);
    event_t red = COLOR(1, 0.2, 0.2, 1);

    proc << memb(renderNorm);

    proc << white << "There was once a time when " << red << "GIANTS" << white <<
    "\\ ruled the land.\nAnd it was not all that great..." << com::input <<
R"(Across the sea and to the Middle East.\
In the cradle of civilization.\
There once was a great man who went on a great journey.\
Enduring even the greatest of obsticles...\)" << com::clear;

    int score = 0;
    std::function<void()> add = [&score]()->void{
        score++;
    };
    std::function<void()> remove = [&score]()->void{
        score--;
    };

    Option opt(c, proc.getTextbox());
    opt.add("I am", [this]()->void{
        proc << "And so sure will be your end..." << com::input;
    });
    opt.add("I am not", [this]()->void{
        proc << "And nor are you sane" << com::input;
    });
    opt.run();

}

void scn::Begin::render() {
    // Thread safe, main thread
    proc.render();
}



