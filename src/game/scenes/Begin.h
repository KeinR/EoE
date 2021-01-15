#ifndef SCN_BEGIN_H_INCLUDED
#define SCN_BEGIN_H_INCLUDED

#include "../../Textbox.h"
#include "../../TextProc.h"
#include "../../core/Node.h"
#include "../../CharRend.h"

class Game;

namespace scn {
    class Begin: public Node {
        Game *game;
        TextProc proc;
        void renderNorm(CharRend::renderObj &obj);
    public:
        Begin(Game &game);

        void script();
        // Main thread
        void render() override;
    };
}

#endif

