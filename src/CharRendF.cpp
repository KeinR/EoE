#include "CharRendF.h"

CharRendF::CharRendF() {
}
CharRendF::CharRendF(const init_t &initFunc, const render_t &renderFunc):
    initFunc(initFunc), renderFunc(renderFunc) {
}


void CharRendF::init(Context &c) {
    if (initFunc) {
        initFunc(c);
    }
}

void CharRendF::render(const renderObj &obj) {
    if (renderFunc) {
        renderFunc(obj);
    }
}

