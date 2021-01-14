#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <string>
#include <memory>
#include <map>
#include <mutex>

#include "Font.h"
#include "CharRend.h"

class Context;

class Textbox {
public:
    typedef std::lock_guard<std::mutex> lockGuard_t;
    typedef std::shared_ptr<CharRend> func_t;
    typedef std::map<std::size_t, func_t> functions_t;
private:
    typedef std::shared_ptr<Font> font_t;

    Context *c;
    font_t font;
    int margin;
    int lineGap;
    int width;
    std::vector<std::pair<std::string, int>> words;
    functions_t functions;
    std::mutex lock;

public:
    Textbox(Context &c, const font_t &font);

    Context *getContext();

    void setMargin(int m);
    void setLineGap(int g);

    void pushChar(char c);
    void pushFunc(const func_t &f);

    void render();
};

#endif

