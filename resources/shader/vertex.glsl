#version 410 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 mColor;

vec3 colorPicker() {

    int index = int(mod(int(gl_VertexID/6), 6));
    //int index = gl_VertexID;

    vec3 result = vec3(1.0f, 1.0f, 1.0f);

    switch(index){
        case 0:
            result = vec3(1.0f, 0.5f, 0.31f);
            break;
        case 1:
            result = vec3(0.3f, 0.3f, 0.3f);
            break;
        case 2:
            result = vec3(0.7f, 0.7f, 0.7f);
            break;
        case 3:
            result = vec3(0.6f, 0.6f, 0.6f);
            break;
        case 4:
            result = vec3(0.5f, 0.5f, 0.5f);
            break;
        case 5:
            result = vec3(0.4f, 0.4f, 0.4f);
            break;
        default:
            result = vec3(0.3f, 0.3f, 0.3f);
            break;
    }

    return result;
}


void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    mColor = colorPicker();
}