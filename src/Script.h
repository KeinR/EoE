#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <thread>
#include <atomic>

class Script {
    std::thread thread;
    std::atomic_bool termFlag;

    void scriptLaunch();

    // Do NOT want to have this extend
    // std::exception, as it should not be
    // caught by wildcards (is different)
    class ThreadInterrupt {
    public:
        ThreadInterrupt() = default;
    };
public:
    Script();
    virtual ~Script() = 0;

    void wait(int millis);
    void joinScript();

    void beginScript();

    virtual void script() = 0;
};


#endif

