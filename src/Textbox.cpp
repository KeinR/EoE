#include "Textbox.h"

#include "core/Context.h"

Textbox::Textbox(Context &c, const font_t &font):
    c(&c),
    font(font),
    margin(0), 
    lineGap(0),
    width(0)
{
}

Context *Textbox::getContext() {
    return c;
}

void Textbox::setMargin(int m) {
    lockGuard_t g(lock);
    margin = m;
}

void Textbox::setLineGap(int v) {
    lockGuard_t g(lock);
    lineGap = v;
}

void Textbox::pushChar(char c) {
    lockGuard_t g(lock);
    if (c == ' ') {
        if (!words.back().first.empty()) {
            words.emplace_back("", 0);
        }
    } else {
        words.back().first.push_back(c);
        words.back().second += font->getWidth(c);
    }
}

void Textbox::pushFunc(const func_t &f) {
    lockGuard_t g(lock);
    functions[words.size()] = f;
}

void Textbox::render() {
    lockGuard_t g(lock);

    functions_t::iterator fit = functions.begin();
    functions_t::iterator fend = functions.end();
    --fend;
    CharRend::renderObj obj;
    obj.font = font;
    obj.height = font->getHeight();
    int x = margin;
    int y = margin;
    for (std::size_t i = 0; i < words.size(); i++) {
        if (fit->first == i && fit != fend) {
            ++fit;
        }
        std::pair<std::string, int> &s = words[i];
        if (width != 0 && obj.x + s.second >= width) {
            x = margin;
            y += font->getHeight() + lineGap;
        }
        obj.word = s.second;
        obj.x = x;
        obj.y = y;
        obj.width = s.second;
        obj.cx = obj.x + obj.width / 2.0f;
        obj.cy = obj.y + obj.height / 2.0f;
        fit->second->render(obj);
    }
}



