#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <memory>

#include "../render/Shader.h"
#include "../Window.h"
#include "../Font.h"

class Context {
public:
    typedef std::shared_ptr<Shader> shader_t;
    typedef std::unique_ptr<Window> window_t;
private:
    window_t window;
    shader_t usedShader;
    int viewportWidth;
    int viewportHeight;

public:
    Context();

    void useShader(const shader_t &shader);
    // Asserts that there is a bound shader
    shader_t getShader();
    Window &getWindow();

    int getVPWidth();
    int getVPHeight();
    void setViewport(int width, int height);



};

#endif

