#ifndef KEYDEFS_H_INCLUDED
#define KEYDEFS_H_INCLUDED

#include "../lib/glfw.h"

enum class key {
    ENTER = GLFW_KEY_ENTER,
    SPACE = GLFW_KEY_SPACE,
    _0 = GLFW_KEY_0,
    _1 = GLFW_KEY_1,
    _2 = GLFW_KEY_2,
    _3 = GLFW_KEY_3,
    _4 = GLFW_KEY_4,
    _5 = GLFW_KEY_5,
    _6 = GLFW_KEY_6,
    _7 = GLFW_KEY_7,
    _8 = GLFW_KEY_8,
    _9 = GLFW_KEY_9,
    NONE = GLFW_KEY_UNKNOWN,
};

namespace keyUtil {
    // Value must be in range [0, 9]
    // If not, key::NONE is returned
    key mapIntToKey(int value);
}

#endif

