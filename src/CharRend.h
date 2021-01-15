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
        std::string text;
        float x;
        float y;
        float wrapWidth;
    };

    virtual ~CharRend() = 0;
    virtual void render(renderObj &obj) = 0;
};

#endif

