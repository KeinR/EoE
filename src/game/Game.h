#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>

#include "../core/Context.h"

class Game {
public:
    typedef std::shared_ptr<Context> ctx_t;
private:
    ctx_t c;
public:
    Game(const ctx_t &c);
    void start();
};

#endif

