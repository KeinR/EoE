#ifndef SCN_TEXT_H_INCLUDED
#define SCN_TEXT_H_INCLUDED

#include <memory>

#include "../../Textbox.h"
#include "../../core/Node.h"

namespace scn {
    class Text: public Node {
        std::shared_ptr<Textbox> disp;
    public:
        Text();
        void render() override;
    };
}


#endif


