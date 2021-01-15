#include "Script.h"

#include <chrono>
#include <stdexcept>
#include <iostream>

using clock_tp = std::chrono::steady_clock;

Script::Script(): termFlag(false) {
}
Script::~Script() {
}

void Script::scriptLaunch() {
    std::set_terminate([]()->void{
        std::cerr << "Script terminated with unhandled exception\n";
    });
    try {
        script();
    } catch (ThreadInterrupt &e) {
        // Interrupt
    }
}

void Script::wait(int millis) {
    auto end = clock_tp::now() + std::chrono::milliseconds(millis);
    do {
        if (termFlag.load()) {
            throw ThreadInterrupt();
        }
    } while (end > clock_tp::now());
}

void Script::joinScript() {
    termFlag.store(true);
    thread.join();
}

void Script::beginScript() {
    thread = std::thread(&Script::scriptLaunch, this);
}

