#include "TextProc.h"

#include <chrono>

#include "Script.h"
#include "Window.h"

TextProc::TextProc(const output_t &out): out(out) {
}

void TextProc::sleep(int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void TextProc::waitEnter() {
    // TODO
    // while (!c.getWindow().keyPressed(Context::key::ENTER)) {
        // sleep(1);
    // }
}

TextProc &TextProc::operator<<(const Textbox::func_t &func) {
    out->pushFunc(func);
    return *this;
}

TextProc &TextProc::operator<<(const std::string &str) {
    for (char c : str) {
        out->pushChar(c);
        if (c != ' ') {
            Script::wait(charCooldownMillis);
        }
    }
    return *this;
} 

TextProc &TextProc::operator<<(int v) {
    *this << std::to_string(v);
    return *this;
}

TextProc &TextProc::operator<<(float v) {
    *this << std::to_string(v);
    return *this;
}


