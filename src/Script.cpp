#include "Script.h"

#include <chrono>

using clock_tp = std::chrono::steady_clock;

Script::Script() {
}
Script::~Script() {
}

void Script::wait(int millis) {
    auto end = clock_tp::now() + std::chrono::milliseconds(millis);
    while (end > clock_tp::now());
}

void Script::beginScript() {
    thread = std::thread(&Script::script, this);
}

