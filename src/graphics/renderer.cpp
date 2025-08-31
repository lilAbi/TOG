#include "renderer.h"

bool Renderer::init() {
    shader = Shader("/Users/abi/CLionProjects/TOG/resources/shader/vertex.glsl",
        "/Users/abi/CLionProjects/TOG/resources/shader/frag.glsl");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute

    return true;
}

void Renderer::draw() {
    //todo: chunk mesh buffer are not clear before new mesh operation happens
    if (sceneGraph.chunksPtr) {
        spdlog::info("Starting Drawing...");

        //get total size of data need to transfer to the gpu
        int bufferSize = 0;
        for (auto& chunk : *(sceneGraph.chunksPtr)) {
            bufferSize += chunk.second.mesh.meshData.size();
        }

        spdlog::critical("This is the buffer size now: {}", bufferSize);
        /*
        if (sceneGraph.redraw == true) {
            //buffer to hold data to the gpu
            std::vector<glm::vec3> buffer;
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

        glm::mat4 projection = glm::perspective(45.0f, static_cast<float>(1920/2) / static_cast<float>(1080/2), 0.1f, 200.0f);
        shader.setMat4("projection", projection);

        //glm::mat4 view = player.getViewMatrix();

        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);

        shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, bufferSize);
        */

        spdlog::info("Finished Drawing!");

    } else {
        spdlog::critical("Drawing ERROR- Nothing to Draw!");
    }
}
