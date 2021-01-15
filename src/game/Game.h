#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>

#include "../core/Context.h"
#include "../Font.h"
#include "../render/Shader.h"

class Game {
public:
    typedef std::shared_ptr<Context> ctx_t;
    typedef std::shared_ptr<Font> font_t;
    typedef std::shared_ptr<Shader> shader_t;
private:
    ctx_t c;
    struct {
        font_t consolas;
    } fonts;
    struct {
        shader_t text;
    } shaders;
public:
    Game(const ctx_t &c);
    void start();
};

#endif

