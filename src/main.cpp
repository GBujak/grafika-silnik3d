#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.hpp>
#include <shader.hpp>

#include <string>
#include <iostream>
#include <alloca.h>

#include <cube.hpp>
#include <enemy.hpp>

constexpr unsigned WIDTH = 1280, HEIGHT = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void process_input(GLFWwindow *window);

Camera default_camera {};

// Time

float delta_time = 0.0f;
float last_frame = 0.0f;

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    auto window = glfwCreateWindow(WIDTH, HEIGHT, "Silnik 3D", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    // SETUP END

    Shader default_shader {"shaders/default.vs", "shaders/default.fs"};

    auto cube_position = glm::vec3(0.0f, 1.0f, -10.0f);
    auto enemy = Enemy(cube_position, default_camera.pos(), Enemy::AiVariant::CircularMovement);

    unsigned VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    default_shader.use();
    auto projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    default_shader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window)) {
        auto current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;


        process_input(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        default_shader.use();
        auto view = default_camera.GetViewMatrix();
        default_shader.setMat4("view", view);

        glBindVertexArray(VAO);
        auto model = glm::mat4(1.0f);
        enemy.update(delta_time, default_camera.pos());
        model = glm::translate(model, enemy.pos());
        default_shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        auto error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "error: " << gluErrorString(error) << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Window resize

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Keyboard

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) default_camera.ProcessKeyboard('w', delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) default_camera.ProcessKeyboard('s', delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) default_camera.ProcessKeyboard('a', delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) default_camera.ProcessKeyboard('d', delta_time);
}

// Mouse

bool first_mouse = true;
float lastX = 1280.0 / 2.0;
float lastY =  720.0 / 2.0;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (first_mouse) {
        lastX = xpos;
        lastY = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    default_camera.ProcessMouseMovement(xoffset, yoffset);
}
