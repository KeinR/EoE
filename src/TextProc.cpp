#include "TextProc.h"

#include <chrono>

#include "Script.h"
#include "Window.h"
#include "core/Context.h"
#include "core/keys.h"

TextProc::TextProc(Context &c):
    TextProc(std::make_shared<Textbox>(c))
{
}
TextProc::TextProc(const output_t &out):
    out(out),
    charCooldownMillis(0)
{
}

void TextProc::sleep(int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void TextProc::waitEnter() {
    while (!out->getContext()->keyPressed(key::ENTER)) {
        sleep(1);
    }
}

void TextProc::setCharCooldown(int millis) {
    charCooldownMillis = millis;
}

TextProc &TextProc::operator<<(const Textbox::func_t &func) {
    out->pushFunc(func);
    return *this;
}

TextProc &TextProc::operator<<(const CharRendF::render_t &func) {
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

TextProc &TextProc::operator<<(command c) {
    switch (c) {
        case enter:
            waitEnter();
            break;
    }
    return *this;
}

void TextProc::render() {
    out->render();
}

