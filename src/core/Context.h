#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <memory>
#include <mutex>

#include "../render/Shader.h"
#include "../Window.h"
#include "../Font.h"
#include "keys.h"

class Context {
public:
    typedef std::shared_ptr<Shader> shader_t;
private:
    typedef std::unique_ptr<Window> window_t;
    typedef std::unordered_map<key, bool> keys_t;
    typedef std::lock_guard<std::mutex> lockGuard_t;

    window_t window;
    shader_t usedShader;
    keys_t keys;
    int viewportWidth;
    int viewportHeight;

    std::mutex inputLock;

public:
    Context();

    void useShader(const shader_t &shader);
    // Asserts that there is a bound shader
    shader_t getShader();
    Window &getWindow();

    // Thread-safe
    bool keyPressed(key k);

    int getVPWidth();
    int getVPHeight();
    void setViewport(int width, int height);

    // Sets the shouldCLose flag on the window
    void close();

    void processInput();

};

#endif

