#ifndef CHARRENDFUNCS_H_INCLUDED
#define CHARRENDFUNCS_H_INCLUDED

#include <functional>

#include "CharRend.h"

class CharRendF: public CharRend {
public:
    typedef std::function<void(Context&)> init_t;
    typedef std::function<void(const renderObj &obj)> render_t;
private:
    init_t initFunc;
    render_t renderFunc;
public:
    CharRendF();
    CharRendF(const init_t &initFunc, const render_t &renderFunc);
    void init(Context &c) override;
    void render(const renderObj &obj) override;
};

#endif

