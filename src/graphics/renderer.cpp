#include "renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "utility/stb_image.h"

bool Renderer::init() {
    shader = Shader("/Users/abi/CLionProjects/TOG/resources/shader/vertex.glsl",
        "/Users/abi/CLionProjects/TOG/resources/shader/frag.glsl");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    spdlog::info("Building Texture Array");
    buildTextureArray();

    return true;
}

void Renderer::draw(Camera& camera) {
    //todo: chunk mesh buffer are not clear before new mesh operation happens
    if (sceneGraph.chunksPtr) {
        spdlog::info("Starting Drawing...");

        //get total size of data need to transfer to the gpu
        int bufferSize = 0;
        for (auto& chunk : *(sceneGraph.chunksPtr)) {
            bufferSize += chunk.second.mesh.meshData.size();
        }

        spdlog::critical("This is the buffer size now: {}", bufferSize);

        if (sceneGraph.redraw == true) {
            //buffer to hold data to the gpu
            std::vector<glm::vec3> buffer;
            buffer.reserve(bufferSize);
            for (auto& chunk : *(sceneGraph.chunksPtr)) {
                buffer.insert(buffer.end(), chunk.second.mesh.meshData.begin(), chunk.second.mesh.meshData.end());
            }

            //bind the buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            //clear the data already in there
            glBufferData(GL_ARRAY_BUFFER, static_cast<int>(sizeof(glm::vec3) * buffer.size()), NULL, GL_DYNAMIC_DRAW);

            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<int>(sizeof(glm::vec3) * buffer.size()), buffer.data());
        }


        shader.use();
        glBindVertexArray(VAO);

        const glm::mat4 projection = glm::perspective(45.0f, static_cast<float>(1920/2) / static_cast<float>(1080/2), 0.1f, 200.0f);
        shader.setMat4("projection", projection);

        const glm::mat4 view = camera.getViewMatrix();

        shader.setMat4("view", view);

        constexpr auto model = glm::mat4(1.0f);

        shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, bufferSize);

        spdlog::info("Finished Drawing!");

    } else {
        spdlog::critical("Drawing ERROR- Nothing to Draw!");
    }
}

void Renderer::buildTextureArray() {
    glGenTextures(1, &textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("/Users/abi/CLionProjects/TOG/resources/texture/grass_block_top.png", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, 0, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::critical("FAILED TO LOAD IMAGE");
    }
}
