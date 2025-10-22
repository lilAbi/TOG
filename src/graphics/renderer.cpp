#include "renderer.h"

bool Renderer::init() {
    shader = Shader("/Users/abi/CLionProjects/TOG/resources/shader/vertex.glsl",
        "/Users/abi/CLionProjects/TOG/resources/shader/frag.glsl");
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &TEXCOORD);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, TEXCOORD);
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
        glBindVertexArray(VAO);

        //get total size of data need to transfer to the gpu
        int bufferSize = 0;
        for (auto& chunk : *(sceneGraph.chunksPtr)) {
            bufferSize += chunk.second.mesh.meshData.size();
        }

        spdlog::critical("This is the buffer size now: {}", bufferSize);

        if (sceneGraph.redraw == true) {
            //buffer to hold data to the gpu
            std::vector<glm::vec3> buffer;
            std::vector<glm::vec3> textureBuffer;
            buffer.reserve(bufferSize);
            textureBuffer.reserve(bufferSize);
            for (auto& chunk : *sceneGraph.chunksPtr) {
                buffer.insert(buffer.end(), chunk.second.mesh.meshData.begin(), chunk.second.mesh.meshData.end());
                textureBuffer.insert(textureBuffer.end(), chunk.second.mesh.textureData.begin(), chunk.second.mesh.textureData.end());
            }

            //bind the buffer containing vertex data, clean it and upload new one
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, static_cast<int>(sizeof(glm::vec3) * buffer.size()), NULL, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<int>(sizeof(glm::vec3) * buffer.size()), buffer.data());

            //bind the buffer containing texture coord data, clean it and upload new one
            glBindBuffer(GL_ARRAY_BUFFER, TEXCOORD);
            glBufferData(GL_ARRAY_BUFFER, static_cast<int>(sizeof(glm::vec3) * textureBuffer.size()), NULL, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<int>(sizeof(glm::vec3) * textureBuffer.size()), textureBuffer.data());

        }

        //glActiveTexture(GL_TEXTURE0 + 0);
        //glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

        shader.use();

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
    //activate the texture
    glActiveTexture(GL_TEXTURE0);
    //generate and build a 2d texture array
    glGenTextures(1, &textureArray);
    //glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //generate the 2d texture array
    //glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, 128, 128, 3, 0, GL_RGB, GL_UNSIGNED_BYTE_3_3_2, nullptr);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 64, 64,3, 0,  GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    //int width, height, nrChannels;
    //const unsigned char* data = stbi_load("/Users/abi/CLionProjects/TOG/resources/texture/grassgrass.png", &width, &height, &nrChannels, 0);

    //load the images into the gpu
    int counter = 0;
    for (auto& path: imagesToLoad) {
        stbi_set_flip_vertically_on_load(true);
        spdlog::info("Loading image at {}", path);
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            if (path.ends_with("leaves.png")) {
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, counter, 64, 64, 1,  GL_RGBA,   GL_UNSIGNED_BYTE, data);
            } else {
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, counter, 64, 64, 1,  GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
        }
        counter++;
        stbi_image_free(data);
    }

    /*
    if (data) {
        //glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, 0, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        spdlog::critical("The size is {} {}", width, height);
        //internal format is how opengl should store the data, format is the data in the loaded image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE_3_3_2, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        spdlog::info("Texture Loaded");
    } else {
        spdlog::critical("FAILED TO LOAD IMAGE");
    }
    */

    //tell opengl which sampler belongs to which shader
    shader.use();
    shader.setInt("textureArray", 0);
}
