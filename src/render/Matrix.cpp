#include "Matrix.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

#include "Shader.h"

#include "../lib/opengl.h"
#include "../core/Context.h"

inline static float ndcX(float x, int winWidth);
inline static float ndcY(float y, int winHeight);
inline static glm::mat4 reflectYAxis(const glm::mat4 &m);

Matrix::Matrix(float x, float y, float pivotXOfs, float pivotYOfs, float width, float height, float rotation, bool reflectAcrossYAxis):
    x(x), y(y), pivotXOfs(pivotXOfs), pivotYOfs(pivotYOfs), width(width), height(height), rotation(rotation), reflectAcrossYAxis(reflectAcrossYAxis) {
}

glm::mat4 Matrix::getModel(bool flipY) {
    float px = pivotXOfs * 2;
    float py = pivotYOfs * 2;
    float fx = x * 2;
    float fy = y * 2;
    float r = -rotation;
    if (flipY) {
        fy = -fy;
        px = -px;
        py = -py;
        r = -r;
    }

    glm::mat4 rot(1.0f);
    rot = glm::translate(rot, glm::vec3(-px , -py, 0));
    rot = glm::rotate(rot, r, glm::vec3(0, 0, 1));
    rot = glm::translate(rot, glm::vec3(px, py, 0));
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(fx, fy, 0));
    if (reflectAcrossYAxis) {
        trans = reflectYAxis(trans);
    }
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 0));

    return trans * rot * scale;
}

void Matrix::load(Context &c, const std::string &location) {

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(-1, 1, 0));
    view = glm::scale(view, glm::vec3(1.0f / c.getVPWidth(), 1.0f / c.getVPHeight(), 0));

    glm::mat4 model = getModel(true);
    glm::mat4 matrix = view * model;

    c.getShader()->setMatrix4fv(location, glm::value_ptr(matrix));
}

float ndcX(float x, int winWidth) {
    return x / winWidth * 2 - 1;
}

float ndcY(float y, int winHeight) {
    return (y / winHeight * 2 - 1) * -1;
}

glm::mat4 reflectYAxis(const glm::mat4 &m) {
    glm::mat4 r(1.0f);
    r[0][0] = -1.0f;

    return m * r;
}
