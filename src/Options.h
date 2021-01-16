#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include <functional>
#include <string>
#include <memory>

#include "core/keys.h"
#include "Font.h"
#include "Textbox.h"

class Options {
public:
    typedef std::function<void()> event_t;
    typedef std::function<float(const std::string&)> strStatFunc_t;
    typedef std::shared_ptr<Font> font_t;
    typedef std::shared_ptr<Textbox> proc_t;
private:
    struct opt_t {
        std::string str;
        event_t func;
        key actuator;
        int width;
        int height;
    };
    std::vector<opt_t> options;
    proc_t proc;
    strStatFunc_t getStringWidth;
    strStatFunc_t getStringHeight;
    int x;
    int y;
    std::size_t selectedIndex;
public:
    Options(const proc_t &p, const strStatFunc_t &width, const strStatFunc_t &height);
    void add(const std::string &prompt, const event_t &e);
    void reset();
    void run();
};

#endif

