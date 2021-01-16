#include "keys.h"

key keyUtil::mapIntToKey(int v) {
    if (v < 0 || v > 9) {
        return key::NONE;
    }
    // This works because of how GLFW keys are structured
    return static_cast<key>(GLFW_KEY_0 + v);
}

