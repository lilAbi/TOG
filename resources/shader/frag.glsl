#version 410 core

out vec4 FragColor;
in vec3 mColor;

uniform sampler2D textureArray;


void main() {
    //FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    FragColor = vec4(mColor, 1.0f);
}