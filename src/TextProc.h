#ifndef TEXTPROC_H_INCLUDED
#define TEXTPROC_H_INCLUDED

#include <memory>

#include "Textbox.h"

class TextProc {
public:
    typedef std::shared_ptr<Textbox> output_t;
    enum command {
        enter
    };
private:
    output_t out;
    int charCooldownMillis;
    void sleep(int millis);
public:
    // Construxts own textbox
    TextProc(Context &c);
    TextProc(const output_t &out);

    void waitEnter();
    void setCharCooldown(int millis);
    
    // Change render func
    TextProc &operator<<(const Textbox::func_t &func);
    TextProc &operator<<(const CharRendF::render_t &func);
    TextProc &operator<<(const std::string &str);
    TextProc &operator<<(int v);
    TextProc &operator<<(float v);
    // Cusotm command
    TextProc &operator<<(command c);

    // JUst calls render() on wrapped Textbox
    void render();
};

#endif


