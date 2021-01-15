#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>
#include <mutex>
#include <atomic>

#include "../core/Context.h"
#include "../Font.h"
#include "../render/Shader.h"
#include "../Script.h"
#include "../core/Node.h"

class Game: public Script {
public:
    typedef std::shared_ptr<Context> ctx_t;
    typedef std::shared_ptr<Font> font_t;
    typedef std::shared_ptr<Shader> shader_t;
    typedef std::shared_ptr<Node> scene_t;
    struct fonts_t {
        font_t consolas;
    };
    struct shaders_t {
        shader_t text;
    };
private:
    typedef std::lock_guard<std::mutex> lockGuard_t;

    ctx_t c;

    fonts_t fonts;
    shaders_t shaders;

    scene_t scene;
    scene_t nextScene;
    std::mutex sceneLock;

    std::atomic_bool endFlag;

    void syncScene();

public:

    Game(const ctx_t &c);
    void setScene(const scene_t &scn);
    Context &getContext();
    fonts_t &getFonts();
    shaders_t &getShaders();
    void script() override;
    void start();
};

#endif

