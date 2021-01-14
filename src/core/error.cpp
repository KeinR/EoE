#include "error.h"

#include <iostream>
#include <stdexcept>

#include "../lib/opengl.h"

err::err(const std::string &loc, bool critical): loc(loc), critical(critical) {
}
err::~err() {
    raise();
}
void err::raise() {
    if (!hasRaised) {
        std::string msg = "Error [" + loc + "]: " + str();
        if (critical) {
            throw std::runtime_error(msg);
        } else {
            std::cerr << msg << '\n';
        }
    }
}

const char *err::glErrStr(int error) {
    switch (error) {
        case GL_NO_ERROR: return "GL_NO_ERROR";
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default: return "-Unknown error-";
    }
}

