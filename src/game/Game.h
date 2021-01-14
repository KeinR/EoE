#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>

#include "../core/Context.h"
#include "../Font.h"

class Game {
public:
    typedef std::shared_ptr<Context> ctx_t;
    typedef std::shared_ptr<Font> font_t;
private:
    ctx_t c;
    font_t font;
public:
    Game(const ctx_t &c);
    void start();
};

#endif

