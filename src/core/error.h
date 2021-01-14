#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <string>
#include <sstream>

class err: public std::stringstream {
    std::string loc;
    bool critical;
    bool hasRaised;
public:
    err(const std::string &loc, bool critical = false);
    ~err();
    void raise();
    static const char *glErrStr(int error);
};

#endif

