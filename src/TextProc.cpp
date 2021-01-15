#include "TextProc.h"

#include <chrono>

#include "Script.h"
#include "Window.h"
#include "core/Context.h"
#include "core/keys.h"

static const char INPUT_WAIT_CHAR = '\\';

TextProc::TextProc(Script &parent, Context &c):
    TextProc(parent, std::make_shared<Textbox>(c))
{
}
TextProc::TextProc(Script &parent, const output_t &out):
    parent(&parent),
    out(out),
    charCooldownMillis(0),
    seekingInput(false),
    lastState(false)
{
}

TextProc::output_t TextProc::getTextbox() {
    return out;
}

bool TextProc::hasInput() {
    bool state = out->getContext().keyPressed(key::ENTER) ||
        out->getContext().keyPressed(key::SPACE);
    // Keys must all be released after a press
    bool result = lastState == state ? false : state;
    lastState = state;
    return result;
}

void TextProc::waitInput() {
    while (!hasInput()) {
        parent->wait(1);
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
        *this << c;
    }
    return *this;
}

TextProc &TextProc::operator<<(char c) {
    if (seekingInput) {
        if (c == INPUT_WAIT_CHAR) {
            seekingInput = false;
            waitInput();
        } else {
            out->pushChar(c);
        }
    } else {
        if (c == INPUT_WAIT_CHAR) {
            waitInput();
        } else {
            out->pushChar(c);
            if (c != ' ') {
                parent->wait(charCooldownMillis);
            }
            seekingInput = hasInput();
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
        case input:
            seekingInput = false;
            waitInput();
            break;
    }
    return *this;
}

void TextProc::render() {
    out->render();
}

