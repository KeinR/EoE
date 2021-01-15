#include "Font.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <exception>

#include "core/error.h"
#include "core/debug.h"
#include "render/Mesh.h"
#include "lib/opengl.h"

// static constexpr int VERTEX_SIZE = 8;
// Knock off colors and we get...
static constexpr int VERTEX_SIZE = 4;


static int readInt(std::ifstream &file) {
    return  (static_cast<unsigned int>(file.get()) << 0) |
            (static_cast<unsigned int>(file.get()) << 8) |
            (static_cast<unsigned int>(file.get()) << 16) |
            (static_cast<unsigned int>(file.get()) << 24);
}

Font::Font(const std::string &path):
    atlas({
        GL_CLAMP_TO_EDGE,
        GL_CLAMP_TO_EDGE,
        GL_NEAREST,
        GL_NEAREST
    })
{

    failed = true;

    static const char *const funcSig = "Font::Font";

    std::ifstream file(path, std::ios::binary);
    if (!file.good()) {
        err(funcSig) << "Failed to open \"" << path << "\"";
        return;
    }

    int imgWidth, imgHeight, channels, dataSize; 

    try {
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        // Read header

        if (file.get() != 0xBF || file.get() != 0xF2) {
            err(funcSig) << "BFF File \"" << path << "\" corrupted (header)";
            return;
        }

        imgWidth = readInt(file);
        imgHeight = readInt(file);
        cellWidth = readInt(file);
        cellHeight = readInt(file);
        channels = file.get() / 8;
        startChar = file.get();

        file.read(charWidths.data(), charWidths.size());

        constexpr int HEADER_SIZE = 276;

        file.seekg(0, file.end);
        dataSize = static_cast<int>(file.tellg()) - HEADER_SIZE;
        file.seekg(HEADER_SIZE);

        file.exceptions(std::ifstream::goodbit);

    } catch (std::exception &e) {
        err(funcSig) << "Failed to read BFF file header: " << e.what();
        return;
    }

    if (dataSize == 0) {
        err(funcSig) << "Cannot use empty bitmaps \"" << path << "\"";
        return;
    }

    if (dataSize != imgWidth * imgHeight * channels) {
        err(funcSig) << "BFF File \"" + path + "\" corrupted (size discrepancy)";
        return;
    }

    int format = Texture::getFormat(channels);

    if (format == 0) {
        err(funcSig) << "BFF File \"" << path << "\" corrupted (channels)";
    }

    char *data = new char[dataSize];
    file.read(data, dataSize);

    atlas.setData(format, imgWidth, imgHeight, reinterpret_cast<unsigned char*>(data));

    delete[] data;

    if (!file.good()) {
        err(funcSig) << "Failed to read data chunk from BFF file \"" << path << "\"";
        // return // Don't return, as we can at the very least set metadata so that the font MIGHT be usable
    } else {
        failed = false;
    }

    rowSize = imgWidth / cellWidth;
    int columnSize = imgHeight / cellHeight;
    endChar = std::min(startChar + rowSize * columnSize - 1, 255);
    texX = (static_cast<float>(cellWidth) * rowSize / imgWidth) / rowSize;
    texY = (static_cast<float>(cellHeight) * columnSize / imgHeight) / columnSize;
    texBase = {
        0, texY,
        0, 0,
        texX, 0,
        texX, texY
    };
}

bool Font::isFailed() {
    return failed;
}

int Font::getWidth(char_t c) const {
    return charWidths[c];
}
int Font::getWidth(const std::string &str) const {
    int result = 0;
    for (char c : str) {
        result += getWidth(c);
    }
    return result;
}
int Font::getLinesWidth(const std::string &str) const {
    int most = 0;
    int current = 0;
    for (char c : str) {
        if (c == '\n') {
            if (current > most) {
                most = current;
            }
            current = 0;
        } else {
            current += getWidth(c);
        }
    }
    return most > current ? most : current;
}
int Font::getHeight() const {
    return cellHeight;
}

int Font::getLinesHeight(const std::string &str) const {
    int result = getHeight();
    for (char c : str) {
        if (c == '\n') {
            result += getHeight();
        }
    }
    return result;
}

Font::wrapResult Font::wrapText(const std::string &text, int wrapWidth, int lineGap, int x, int y) {
    wrapResult result;
    result.x = x;
    result.y = y;
    result.width = 0;
    result.height = 0; 
    result.text.reserve(text.size() + 5);
    int vertStep = lineGap + getHeight();
    int mostWidth = 0;
    for (char c : text) {
        int nWidth = getWidth(c);
        if (nWidth + result.x > wrapWidth || c == '\n') {
            if (result.x > mostWidth) {
                mostWidth = result.x;
            }
            result.text.push_back('\n');
            result.x = 0;
            result.y += vertStep;
            if (c == '\n') {
                continue;
            }
        }
        result.x += nWidth;
        result.text.push_back(c);
    }
    if (result.x > mostWidth) {
        mostWidth = result.x;
    }
    result.width = mostWidth;
    result.cx = result.width / 2.0f;
    /*
    if (result.y == y) {
        result.width = result.x - x;
        result.cx = result.x / 2.0f;
    } else {
        result.width = mostWidth;
        result.cx = result.width / 2.0f;
    }
    */
    result.height = result.y - y + getHeight();
    result.cy = y + result.height / 2.0f;

    return result;
}

void Font::bindAtlas() {
    atlas.bind();
}

void Font::getRenderData(std::vector<float> &vertices, std::vector<unsigned int> &indices, const std::string &str, int xi, int lineGap) const {
    EOE_ASSERT(str.size() > 0);

    vertices.reserve(vertices.size() + str.size() * 4 * 2 + str.size() * 4);
    indices.reserve(indices.size() + str.size() * 3 * 2);

    int wp = xi;
    for (char c : str) {
        if (c == '\n') {
            break;
        }
        wp += getWidth(c);
    }
    const float vWidth = std::max(wp, getLinesWidth(str));
    const int vHeight = std::count(str.begin(), str.end(), '\n') * (lineGap + getHeight()) + getHeight(); 
    
    const float scaleY = static_cast<float>(getHeight()) / vHeight;
    // TODO: ntext line offset of the first char in that line...
    const float nStartX = -1.0f + (getWidth(str[0]) / 2.0f + 0.5f) / vWidth * 2;
    // const float xofs = static_cast<float>(xi) / vWidth;
    const float nStartY = 1.0f - (getHeight() + 0.5f) / vHeight;

    float x = -1.0f + (getWidth(str[0]) / 2.0f + xi + 0.5f) / vWidth * 2;
    // float x = nStartX;
    float y = nStartY;

    const float yStep = static_cast<float>(cellHeight + lineGap) / vHeight * 2 * -1;

    for (unsigned char c : str) {
        if (c == '\n') {
            x = nStartX;
            y += yStep;
        } else if (c < startChar || c > endChar) {
            c = startChar;
        } else {
            int cw = getWidth(c);
            const float scaleX = static_cast<float>(cw) / vWidth;
            const std::array<float, 8> quad = {
                -scaleX, -scaleY,
                -scaleX, scaleY,
                scaleX, scaleY,
                scaleX, -scaleY
            };

            unsigned int vert = vertices.size() / VERTEX_SIZE;
            int index = c - startChar;
            float tx = index % rowSize * texX;
            float ty = index / rowSize * texY;
            for (int i = 0; i < 4; i++) {
                vertices.insert(vertices.end(), {
                    quad[i * 2] + x, quad[i * 2 + 1] + y,
                    texBase[i * 2] + tx, texBase[i * 2 + 1] + ty
                });
            }
            indices.insert(indices.end(), {
                vert + 0, vert + 1, vert + 2,
                vert + 0, vert + 2, vert + 3
            });

            x += static_cast<float>(cw) / vWidth * 2;
        }
    }
}

Mesh Font::genMesh(const std::string &str, int xofs, int lineGap) const {
    Mesh mesh;

    if (str.size() == 0) {
        return mesh;
    }

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    getRenderData(vertices, indices, str, xofs, lineGap);

    mesh.setVertices(vertices.size(), vertices.data());
    mesh.setIndices(indices.size(), indices.data());
    mesh.setParam(0, 2, VERTEX_SIZE, 0); // Position
    mesh.setParam(1, 2, VERTEX_SIZE, 2); // Texture coords
    // mesh.setParam(2, 4, VERTEX_SIZE, 4); // Color

    return mesh;
}

