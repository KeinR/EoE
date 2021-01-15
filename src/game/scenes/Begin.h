#ifndef SCN_BEGIN_H_INCLUDED
#define SCN_BEGIN_H_INCLUDED

#include <array>
#include <memory>

#include "../../Textbox.h"
#include "../../TextProc.h"
#include "../../core/Node.h"
#include "../../CharRend.h"

class Game;

namespace scn {
    class Begin: public Node {
        Game *game;
        TextProc proc;

        /*
        class Color: public CharRend {
        public:
            typedef void(Begin::*func_t)(renderObj&);
            typedef std::array<float, 4> color_t;
        private:
            Begin *parent;
            func_t parentFunc;
            color_t color;
        public:
            Color(Begin &parent, func_t parentFunc, const color_t &color);

            std::shared_ptr<Color> make(Begin &parent, func_t parentFunc, const color_t &color);

            void render(renderObj &obj) override;
        };
        */

        void renderNorm(CharRend::renderObj &obj);
    public:
        Begin(Game &game);

        void script();
        // Main thread
        void render() override;
    };
}

#endif

