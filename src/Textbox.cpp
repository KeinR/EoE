#include "Textbox.h"

#include <stdexcept>

#include "core/Context.h"

Textbox::Textbox(Context &c):
    c(&c),
    margin(0), 
    lineGap(0),
    wrapWidth(0)
{
}

Context &Textbox::getContext() {
    return *c;
}

void Textbox::setMargin(int m) {
    lockGuard_t g(lock);
    margin = m;
}

void Textbox::setLineGap(int v) {
    lockGuard_t g(lock);
    lineGap = v;
}

void Textbox::setWrappingWidth(int w) {
    lockGuard_t g(lock);
    wrapWidth = w;
}

void Textbox::pushChar(char c) {
    lockGuard_t g(lock);
    text.push_back(c);
}


void Textbox::pushString(const std::string &str) {
    lockGuard_t g(lock);
    text += str;
}

void Textbox::prepare(std::size_t count) {
    text.reserve(text.size() + count);
}

void Textbox::pushFunc(const func_t &f) {
    lockGuard_t g(lock);
    functions[text.size()] = f;
    lastFunc = f;
}

void Textbox::pushFunc(const CharRendF::render_t &func) {
    pushFunc(std::make_shared<CharRendF>(func));
}

void Textbox::pushEvent(const event_t &e) {
    lockGuard_t g(lock);
    if (!lastFunc) {
        throw std::logic_error("No functions pushed");
    }
    func_t wFunc = lastFunc;
    functions[text.size()] = std::make_shared<CharRendF>(
        [e, wFunc](CharRend::renderObj &obj)->void{
            e();
            wFunc->render(obj);
        }
    );
}

void Textbox::clear() {
    lockGuard_t g(lock);

    if (!functions.empty()) {
        lastFunc = functions.begin()->second;
    } else {
        // Just to be sure
        lastFunc.reset();
    }

    functions.clear();
    events.clear();
    text.clear();

    if (lastFunc) {
        functions[0] = lastFunc;
    }
}

void Textbox::render() {
    lockGuard_t g(lock);

    CharRend::renderObj obj;
    obj.c = c;
    obj.x = margin;
    obj.y = margin;
    obj.wrapWidth = wrapWidth - margin * 2;
    obj.text.reserve(text.size());

    for (functions_t::iterator fit = functions.begin(); fit != functions.end();) {
        functions_t::iterator tf = fit;
        ++fit;
        std::size_t begin = tf->first;
        std::size_t end;
        if (fit != functions.end()) {
            end = fit->first;
        } else {
            end = text.size();
        }
        obj.text.assign(text.begin() + begin, text.begin() + end); 
        tf->second->render(obj);
    }
}



