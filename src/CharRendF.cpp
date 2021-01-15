#include "CharRendF.h"

CharRendF::CharRendF() {
}
CharRendF::CharRendF(const render_t &renderFunc):
    renderFunc(renderFunc) {
}

void CharRendF::render(renderObj &obj) {
    if (renderFunc) {
        renderFunc(obj);
    }
}

