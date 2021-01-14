#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D atlas;
uniform vec4 color;

void main() {
    float alpha = texture(atlas, texCoords).r;
    FragColor = color * alpha;
}

