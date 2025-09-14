#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <list>
#include <map>

#include "include/stb_image.h"
#include "src/render/shader_program.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/app/application.h"
#include "src/render/camera.h"
#include "src/render/geometry_generator.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


Camera camera{};

int main() {
    // glfw: initialize and configure
    // ------------------------------
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //
    // // glfw window creation
    // // --------------------
    // GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    // if (window == nullptr) {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSwapInterval(0);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // // glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    // glfwSetCursorPosCallback(window, mouse_callback);
    //
    // // glad: load all OpenGL function pointers
    // // ---------------------------------------
    // if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    //
    // glEnable(GL_DEPTH_TEST);
    //
    // // Build and compile shaders
    // const Shader lightingShader("basic_lighting");
    //
    // const glm::vec3 lightCubePos(0.0f, 2.0f, 0.0f);
    // // world space positions of our cubes
    // glm::vec3 cubePositions[] = {
    //     glm::vec3(0.0f, 0.0f, 0.0f),
    //     glm::vec3(2.0f, 5.0f, -15.0f),
    //     glm::vec3(-1.5f, -2.2f, -2.5f),
    //     glm::vec3(-3.8f, -2.0f, -12.3f),
    //     glm::vec3(2.4f, -0.4f, -3.5f),
    //     glm::vec3(-1.7f, 3.0f, -7.5f),
    //     glm::vec3(1.3f, -2.0f, -2.5f),
    //     glm::vec3(1.5f, 2.0f, -2.5f),
    //     glm::vec3(1.5f, 0.2f, -1.5f),
    //     glm::vec3(-1.3f, 1.0f, -1.5f)
    // };
    //
    // auto cube_data = MeshGenerator::generateShape(MeshGenerator::ShapeType::Cube);
    // unsigned int VBO, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // glBindVertexArray(VAO);
    //
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER,
    //              static_cast<GLsizeiptr>(cube_data.vertices.size() * sizeof(MeshGenerator::Vertex)),
    //              cube_data.vertices.data(),
    //              GL_STATIC_DRAW);
    //
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //              static_cast<GLsizeiptr>(cube_data.indices.size() * sizeof(MeshGenerator::Vertex)),
    //              cube_data.indices.data(),
    //              GL_STATIC_DRAW);
    //
    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void *>(0));
    // glEnableVertexAttribArray(0);
    // // Normal attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // // Texture coordinates (2 floats starting at offset 3 * sizeof(float))
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    //
    // // unsigned int texture;
    // // glGenTextures(1, &texture);
    // // glBindTexture(GL_TEXTURE_2D, texture);
    // // // all upcoming GL_TEXTURE_2D operations now have an effect on this texture object
    // // // set the texture wrapping parameters
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // // // set texture wrapping to GL_REPEAT (default wrapping method)
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // // set texture filtering parameters
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // // // load image, create texture and generate mipmaps
    // // int width, height, nrChannels;
    // // unsigned char *data = stbi_load("../resources/grey-brick.jpg", &width, &height, &nrChannels, 0);
    // // if (data) {
    // //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // //     glGenerateMipmap(GL_TEXTURE_2D);
    // // } else {
    // //     std::cout << "Failed to load texture" << std::endl;
    // // }
    // // stbi_imag
    // Shader lightCubeShader("basic.vert", "basic.frag");
    // unsigned int lightCubeVAO, lightCubeVBO;
    // glGenBuffers(1, &lightCubeVBO);
    //
    // glGenVertexArrays(1, &lightCubeVAO);
    // glBindVertexArray(lightCubeVAO);
    //
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //
    // // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void *>(0));
    // glEnableVertexAttribArray(0);
    //
    // lightingShader.use();
    // glm::mat4 projection = glm::perspective(glm::radians(90.0f),
    //                                         static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f,
    //                                         100.0f);
    // lightingShader.setMat4("projection", projection);
    // lightCubeShader.use();
    // lightCubeShader.setMat4("projection", projection);;
    //
    //
    // // render loop
    // while (!glfwWindowShouldClose(window)) {
    //     // input
    //     const float currentFrame = glfwGetTime();
    //     deltaTime = currentFrame - lastFrame;
    //     lastFrame = currentFrame;
    //     processInput(window);
    //
    //     // render
    //     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //
    //     // glBindTexture(GL_TEXTURE_2D, texture);
    //
    //     // get matrix's uniform location and set matrix
    //     lightingShader.use();
    //     lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    //     lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    //     lightingShader.setVec3("lightPos", lightCubePos);
    //     lightingShader.setVec3("viewPos", camera.getPos());
    //     glm::mat4 view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), camera.getWorldUp());
    //     lightingShader.setMat4("view", view);
    //
    //     glBindVertexArray(VAO);
    //
    //
    //     for (unsigned int i = 0; i < 10; i++) {
    //         // calculate the model matrix for each object and pass it to shader before drawing
    //         auto model = glm::mat4(1.0f);
    //         model = glm::translate(model, cubePositions[i]);
    //         const float angle = 0.0f * i;
    //         model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //         lightingShader.setMat4("model", model);
    //
    //         glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //     }
    //     lightCubeShader.use();
    //     lightCubeShader.setMat4("view", view);
    //     auto model = glm::mat4(1.0f);
    //     model = glm::translate(model, lightCubePos);
    //     model = glm::scale(model, glm::vec3(0.2f));
    //     lightCubeShader.setMat4("model", model);
    //     glBindVertexArray(lightCubeVAO);
    //     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }
    //
    // // glfw: terminate, clearing all previously allocated GLFW resources.
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glfwTerminate();
    Application app{};
    app.run();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

// void processInput(GLFWwindow *window) {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
//
//     for (const auto &[key, direction]: moveKeys) {
//         if (glfwGetKey(window, key) == GLFW_PRESS)
//             camera.ProcessKeyboard(direction, deltaTime);
//     }
// }
//
// struct CENTER {
//     static constexpr float x = SCR_WIDTH / 2.0f;
//     static constexpr float y = SCR_HEIGHT / 2.0f;
// };
//
// void mouse_callback(GLFWwindow *window, const double xpos, const double ypos) {
//     camera.ProcessMouseMovement(xpos - CENTER::x, CENTER::y - ypos);
//     glfwSetCursorPos(window, CENTER::x, CENTER::y);
// }
//
// // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//     // make sure the viewport matches the new window dimensions; note that width and
//     // height will be significantly larger than specified on retina displays.
//     glViewport(0, 0, width, height);
// }
