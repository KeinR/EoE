#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <thread>

class Script {
    std::thread thread;
public:
    Script();
    virtual ~Script() = 0;

    static void wait(int millis);

    void beginScript();

    virtual void script() = 0;
};


#endif

