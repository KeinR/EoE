#include "Texture.h"

#include <cstddef>

#include "../lib/opengl.h"

// In-use enum values for Texture.
// def'd to be extra safe.
#define TEXTURE_TYPE GL_TEXTURE_2D
#define TEXTURE_PIXEL_TYPE GL_UNSIGNED_BYTE

// Default parameters.
constexpr Texture::tparam Texture::defaultParams{
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_EDGE,
    GL_LINEAR,
    GL_LINEAR
};

Texture::Texture() {
    init(defaultParams);
}

Texture::Texture(const tparam &param) {
    init(param);
}

Texture::~Texture() {
    deInit();
}

void Texture::init(const tparam &params) {
    glGenTextures(1, &buffer);
    setParams(params);
}

void Texture::deInit() {
    glDeleteTextures(1, &buffer);
}

void Texture::steal(Texture &other) {
    buffer = other.buffer;
    other.buffer = 0;
}

Texture::Texture(Texture &&other) {
    steal(other);
}
Texture &Texture::operator=(Texture &&other) {
    steal(other);
    return *this;
}

void Texture::setData(int fmt, unsigned int width, unsigned int height, const data_t *data) {
    bind();
    glTexImage2D(TEXTURE_TYPE, 0, fmt, width, height, 0, fmt, TEXTURE_PIXEL_TYPE, data);
    unbind();
}

unsigned int Texture::getHandle() {
    return buffer;
}

void Texture::bind() {
    glBindTexture(TEXTURE_TYPE, buffer);
}
void Texture::unbind() {
    glBindTexture(TEXTURE_TYPE, 0);
}

void Texture::clear() {
    bind();
    glTexImage2D(TEXTURE_TYPE, 0, GL_RED, 0, 0, 0, GL_RED, TEXTURE_PIXEL_TYPE, NULL);
    unbind();
}

void Texture::setDefaultParams() {
    setParams(defaultParams);
}
void Texture::setParams(const tparam &params) {
    bind();

    // x/y wrap parameter
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_WRAP_S, params.xWrap);
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_WRAP_T, params.yWrap);

    // min/max filtering parameter
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_MIN_FILTER, params.minFilter);
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_MAG_FILTER, params.maxFilter);

    unbind();
}

int Texture::getFormat(int channels) {
    switch (channels) {
        case 4: return GL_RGBA;
        case 3: return GL_RGB;
        case 2: return GL_RG;
        case 1: return GL_RED;
        default: return 0;
    }
}
