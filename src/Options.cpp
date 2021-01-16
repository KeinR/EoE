#include "Options.h"

#include <stdexcept>

#include "TextProc.h"
#include "Textbox.h"
#include "render/Shader.h"
#include "core/Context.h"

Options::Options(const proc_t &p, const strStatFunc_t &width, const strStatFunc_t &height):
    proc(p), getStringWidth(width), getStringHeight(height), x(0), y(0), selectedIndex(-1) {
}

void Options::add(const std::string &prompt, const event_t &e) {
    std::size_t number = options.size() + 1; // Start at one
    if (number > 9) {
        throw std::invalid_argument("Too many options");
    }
    opt_t o;
    o.str = "    [" + std::to_string(number) + "] " + prompt;
    o.func = e;
    o.actuator = keyUtil::mapIntToKey(number);
    o.width = getStringWidth(o.str);
    o.height = getStringHeight(o.str);
    options.push_back(o);
}

void Options::reset() {
    options.clear();
}

void Options::run() {
    if (options.empty()) {
        return;
    }

    typedef Textbox::event_t event_t;

    Context &c = proc->getContext();

    event_t blueBg = [&c]()->void{
        c.getShader()->set4f("background", 0, 1, 0, 1);
    };
    event_t clearBg = [&c]()->void{
        c.getShader()->set4f("background", 0, 0, 0, 0);
    };

    proc->pushChar('\n');
    /*
    proc->pushEvent([this]()->void{
        x =
    });
    */

    for (std::size_t i = 0; i < options.size(); i++) {
        proc->pushEvent([this, i, &c]()->void{
            if (selectedIndex == i) {
                c.getShader()->set4f("background", 0, 0.6, 0, 1);
            }
        });
        proc->pushString(options[i].str);
        proc->pushEvent(clearBg);
    }

    constexpr std::size_t none = -1; 
    std::size_t selected = none;
    while (selected == none) {
        for (std::size_t i = 0; i < options.size() && selected == none; i++) {
            if (c.keyPressed(options[i].actuator)) {
                selected = i;
            }
        }
        float mx = c.getMouseX();
        float my = c.getMouseY();
        /*
        if () {

        }
        */

    }

}

