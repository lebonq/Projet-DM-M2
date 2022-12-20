#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/FilePath.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include "Map.hpp"
int window_width  = 1920;
int window_height = 1080;

int old_xpos = 0.f;
int old_ypos = 0.f;

glm::mat4 PMatrix,VMatrix,MMatrix;
FreeflyCamera camera;

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        camera.moveFront(2.0f);
    }

    if(key == GLFW_KEY_S && action == GLFW_PRESS){
        camera.moveFront(-2.0f);
    }

    if(key == GLFW_KEY_D && action == GLFW_PRESS){
        camera.moveLeft(-2.0f);
    }

    if(key == GLFW_KEY_A && action == GLFW_PRESS){
        camera.moveLeft(2.0f);
    }
    if(key == GLFW_KEY_ESCAPE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double /*yoffset*/)
{
}

static void cursor_position_callback(GLFWwindow* /*window*/, double xpos, double ypos)
{
    camera.rotateLeft((old_xpos - xpos)/20);
    camera.rotateUp((old_ypos - ypos)/20);
    old_xpos = xpos;
    old_ypos = ypos;
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    window_width  = width;
    window_height = height;
    int frame_width = 0;
    int frame_height = 0;
    glfwGetFramebufferSize(window,&frame_width,&frame_height);
    glViewport(0, 0, frame_width, frame_height);
    PMatrix = glm::perspective(glm::radians(70.0f),static_cast<float>(window_width)/static_cast<float>(window_height),0.1f,100.f);
}

int main()
{
    Map map1("assets/map1");
    return 0;
}