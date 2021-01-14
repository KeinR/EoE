#ifndef CHARREND_H_INCLUDED
#define CHARREND_H_INCLUDED

#include <string>
#include <memory>

#include "Font.h"

class Context;

class CharRend {
public:

    struct renderObj {
        Context *c;
        std::shared_ptr<Font> font;
        std::string word;
        // X position of the beginning of the word (top-left)
        int x;
        // Y of the beginning (top-left)
        int y;
        // Center coordinate of word (x|y + (width|height)/2)
        float cx;
        float cy;
        // Width in px
        int width;
        // Height in px
        int height;
    };

    virtual ~CharRend() = 0;
    virtual void init(Context &c) = 0;
    virtual void render(const renderObj &obj) = 0;
};

#endif

