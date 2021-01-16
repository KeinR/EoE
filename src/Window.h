#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <unordered_map>

#include "WindowEventCallback.h"

struct GLFWwindow;

class Window: private WindowEventCallback {
    GLFWwindow *handle;

    void deInit();

public:

    Window(const char *title, int width, int height);
    ~Window();

    void registerCallback(WindowEventCallback &callback);

    bool valid();

    GLFWwindow *getHandle();

    void makeCurrent();
    void swapBuffers();
    void show();
    void hide();

    bool keyPressed(int e);

    void getMousePos(float &x, float &y);
    void getFBSize(int &w, int &h);
    int getFBWidth();
    int getFBHeight();

    void setSize(int w, int h);
    void setTitle(const char *str);

    bool shouldClose();
    void setShouldClose(bool t);

    static void pollEvents();
};

#endif

