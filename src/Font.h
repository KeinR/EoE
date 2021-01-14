#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <array>
#include <string>
#include <vector>

#include "render/Texture.h"

class Mesh;

class Font {
public:
    typedef unsigned char char_t;
private:
    char_t startChar; // Inclusive
    char_t endChar; // Inclusive
    Texture atlas;
    std::array<char, 256> charWidths;
    std::array<float, 8> texBase;
    int cellWidth;
    int cellHeight;
    int rowSize;
    float texX;
    float texY;
    bool failed;

public:

    // Binary Font Format (.bff) font, Codehead's
    // Bitmap Font Generator's native output. 
    Font(const std::string &path);

    bool isFailed();

    int getWidth(char_t c) const;
    int getWidth(const std::string &str) const;
    int getLinesWidth(const std::string &str) const;
    int getHeight() const;
    int getLinesHeight(const std::string &str) const;

    void bindAtlas();

    void getRenderData(
        std::vector<float> &vertices, std::vector<unsigned int> &indices,
        const std::string &str
    ) const;

    // Will make newline when encountering \n char.
    Mesh genMesh(const std::string &str) const;
};

#endif
