#ifndef TEXTPROC_H_INCLUDED
#define TEXTPROC_H_INCLUDED

#include <memory>

#include "Textbox.h"

class Script;

class TextProc {
public:
    typedef std::shared_ptr<Textbox> output_t;
    enum command {
        input
    };
private:
    Script *parent;
    output_t out;
    int charCooldownMillis;
    bool seekingInput;
    bool lastState;

    bool hasInput();
public:
    // Construxts own textbox
    TextProc(Script &parent, Context &c);
    TextProc(Script &parent, const output_t &out);

    output_t getTextbox();

    void waitInput();
    void setCharCooldown(int millis);
    
    // Change render func
    TextProc &operator<<(const Textbox::func_t &func);
    TextProc &operator<<(const CharRendF::render_t &func);
    TextProc &operator<<(const std::string &str);
    TextProc &operator<<(char c);
    TextProc &operator<<(int v);
    TextProc &operator<<(float v);
    // Cusotm command
    TextProc &operator<<(command c);

    // JUst calls render() on wrapped Textbox
    void render();
};

#endif


