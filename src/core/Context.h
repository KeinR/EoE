#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <memory>
#include <mutex>
#include <atomic>

#include "../render/Shader.h"
#include "../Window.h"
#include "../WindowEventCallback.h"
#include "../Font.h"
#include "keys.h"

class Context: private WindowEventCallback {
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
    std::atomic<float> mouseX;
    std::atomic<float> mouseY;
    std::atomic_bool leftMousePressed;

public:
    Context();

    void keyEvent(int key, int action, int mods) override;
    void mouseMoveEvent(float x, float y) override;
    void mouseButtonEvent(int button, int action, int mods) override;

    void useShader(const shader_t &shader);
    // Asserts that there is a bound shader
    shader_t getShader();
    Window &getWindow();

    // Thread-safe
    bool keyPressed(key k);

    int getVPWidth();
    int getVPHeight();
    void setViewport(int width, int height);

    // These three are thread safe
    float getMouseX();
    float getMouseY();
    bool isLeftMousePressed();

    // Sets the shouldCLose flag on the window
    void close();

    void processInput();

};

#endif

