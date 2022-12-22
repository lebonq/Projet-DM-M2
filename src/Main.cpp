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
#include "ModelsManager.hpp"
int window_width  = 1920;
int window_height = 1080;

int old_xpos = 0.f;
int old_ypos = 0.f;

glm::mat4 PMatrix,VMatrix,MMatrix;
FreeflyCamera camera;

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        camera.moveFront(0.5f);
    }

    if(key == GLFW_KEY_S && action == GLFW_PRESS){
        camera.moveFront(-0.5f);
    }

    if(key == GLFW_KEY_D && action == GLFW_PRESS){
        camera.moveLeft(-0.5f);
    }

    if(key == GLFW_KEY_A && action == GLFW_PRESS){
        camera.moveLeft(0.5f);
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
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "TP6", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Default proj matrix
    PMatrix = glm::perspective(glm::radians(70.0f),static_cast<float>(window_width)/static_cast<float>(window_height),0.1f,100.f);

    //For 3D
    glEnable(GL_DEPTH_TEST);

    Map map("assets/map1");
    ShadersManager& shadersMana = map.getShadersManager();

        //float rotate = 0.f;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        VMatrix = camera.getViewMatrix();

        glUniformMatrix4fv(shadersMana.getPMatrix(),1,GL_FALSE,glm::value_ptr(PMatrix));
        glUniformMatrix4fv(shadersMana.getVMatrix(),1,GL_FALSE,glm::value_ptr(VMatrix));


        glm::vec3 lightPos = camera.getPosition();
        glm::vec3 lightIntensity = glm::vec3(1);

        glUniform3fv(shadersMana.getLightPosVs(),1,glm::value_ptr(glm::vec3(VMatrix*glm::vec4(lightPos,1.0f))));
        glUniform3fv(shadersMana.getLightIntensity(),1,glm::value_ptr(lightIntensity));

        map.draw();

        //Swap front and back buffers
        glfwSwapBuffers(window);
        //Poll for and process events
        glfwPollEvents();
    }
    glUseProgram(0);
}