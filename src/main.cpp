#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.hpp>
#include <shader.hpp>
#include <mesh.hpp>

#include <string>
#include <iostream>
#include <alloca.h>

#include <cube.hpp>
#include <enemy.hpp>

#include <globals.hpp>
#include <player.hpp>
#include <world.hpp>
#include <floor.hpp>
#include <crosshair.hpp>

#include <renderer.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void process_input(GLFWwindow *window);

Player player;
World world;

// Time

float delta_time = 0.0f;
float last_frame = 0.0f;

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    srand(0);

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
    auto cube_mesh = Mesh{ cube_vertices, 36 * 3 };

    Shader floor_shader {"shaders/floor.vs", "shaders/floor.fs"};
    Mesh floor_mesh { floor_vertices, 6 * 3 };

    Shader crosshair_shader {"shaders/crosshair.vs", "shaders/crosshair.fs"};
    Mesh crosshair_mesh { crosshair_vertices, 12 * 3 };

    auto renderer = Renderer {
        default_shader,   cube_mesh,
        floor_shader,     floor_mesh,
        crosshair_shader, crosshair_mesh,
        player.cam()
    };
    
    while (!glfwWindowShouldClose(window)) {
        auto current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // auto f = player.cam().aim_vector();
        // std::cout << "Front: " << f.x << " " << f.y << " " << f.z << std::endl;

        process_input(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world.update(current_frame, delta_time, player.cam().pos());
        for (auto& e: world.enemies()) 
            renderer.draw_enemy(e);
        renderer.draw_floor();

        renderer.draw_crosshair(player.can_shoot(current_frame));

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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) player.cam().ProcessKeyboard('w', delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) player.cam().ProcessKeyboard('s', delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) player.cam().ProcessKeyboard('a', delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) player.cam().ProcessKeyboard('d', delta_time);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) player.try_shoot(glfwGetTime(), world);
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

    player.cam().ProcessMouseMovement(xoffset, yoffset);
}
