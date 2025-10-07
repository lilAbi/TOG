#version 410 core

out vec4 FragColor;
in vec3 texData;

//uniform sampler2D textureArray;
uniform sampler2DArray textureArray;

void main() {
    //FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    if( texData.z == 0){
        FragColor = texture(textureArray, texData) * vec4(0.365, 0.522, 0.184, 0.0);
    } else if (texData.z == 1) {
        FragColor = texture(textureArray, texData);// * vec4(0.56, 0.2558, 0.0159, 0.0);
    } else {
        FragColor = texture(textureArray, texData) * vec4(0.365, 0.522, 0.184, 0.0);
    }
    //FragColor = texture(textureArray, vec2(texData.x, texData.y)) * vec4(0.365, 0.522, 0.184, 0.0);
}