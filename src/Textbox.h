#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <string>
#include <memory>
#include <map>
#include <mutex>

#include "Font.h"
#include "CharRend.h"
#include "CharRendF.h"

class Context;

class Textbox {
public:
    typedef std::lock_guard<std::mutex> lockGuard_t;
    typedef std::shared_ptr<CharRend> func_t;
    typedef std::map<std::size_t, func_t> functions_t;
private:

    Context *c;
    int margin;
    int lineGap;
    int wrapWidth;
    std::string text;
    functions_t functions;
    std::mutex lock;

public:
    Textbox(Context &c);

    Context *getContext();

    void setMargin(int m);
    void setLineGap(int g);
    void setWrappingWidth(int w);

    void pushChar(char c);
    void pushString(const std::string &str);
    void prepare(std::size_t count);
    void pushFunc(const func_t &f);
    void pushFunc(const CharRendF::render_t &func);

    // Main thread
    void render();
};

#endif

