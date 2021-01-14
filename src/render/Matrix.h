#ifndef DANZUN_MATRIX_H_INCLUDED
#define DANZUN_MATRIX_H_INCLUDED

#include <string>

#include <glm/glm.hpp>

class Context;

class Matrix {
    glm::mat4 model;
public:
    // [In screen coords]

    // Translation
    float x;
    float y;
    // Pivot relative to x/y (in NDC)
    float pivotXOfs;
    float pivotYOfs;
    // Scaling
    float width;
    float height;

    // Rotation
    // [In radians]
    float rotation;

    bool reflectAcrossYAxis;

    Matrix(float x = 0, float y = 0, float pivotXOfs = 0, float pivotYOfs = 0, float width = 10, float height = 10, float rotation = 0, bool reflectAcrossYAxis = false);

    glm::mat4 getModel(bool flipY);

    void load(Context &c, const std::string &location = "model");

    void trans();
    void scale();
    void rotate();
};

#endif
