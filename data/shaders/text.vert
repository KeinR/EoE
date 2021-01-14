#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCoords;

out vec2 texCoords;

uniform mat4 model;

void main() {
    gl_Position = model * vec4(aPos, 0, 1);
    // gl_Position = vec4(aPos, 0, 1);
    texCoords = aCoords;
}


