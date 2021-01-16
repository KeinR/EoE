#ifndef WINDOWEVENTCALLBACK_H_INCLUDED
#define WINDOWEVENTCALLBACK_H_INCLUDED

class WindowEventCallback {
public:
    virtual ~WindowEventCallback() = 0;
    virtual void keyEvent(int key, int action, int mods);
    virtual void mouseMoveEvent(float x, float y);
    virtual void mouseButtonEvent(int button, int action, int mods);
};

#endif

