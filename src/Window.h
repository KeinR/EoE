#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

struct GLFWwindow;

class Window {
    GLFWwindow *handle;

    void deInit();

public:

    Window(const char *title, int width, int height);
    ~Window();

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

    static void pollEvents();
};

#endif

