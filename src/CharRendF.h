#ifndef CHARRENDFUNCS_H_INCLUDED
#define CHARRENDFUNCS_H_INCLUDED

#include <functional>

#include "CharRend.h"

class CharRendF: public CharRend {
public:
    typedef std::function<void(renderObj &obj)> render_t;
private:
    render_t renderFunc;
public:
    CharRendF();
    CharRendF(const render_t &renderFunc);
    void render(renderObj &obj) override;
};

#endif

