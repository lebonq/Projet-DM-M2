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
FreeflyCamera* camera;
int rotation = 0;
float doneRotation = 0;
float doneRotation_real = 0;

int move = 0;
bool moveFront = false;
float doneMove = 0;
float doneMove_real = 0;
double prevTime;

Map* map;
Player* player;

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if(key == GLFW_KEY_W && action == GLFW_PRESS && rotation == 0 && move == 0){
        //camera->moveFront(1.0f);
        move = 1;
        prevTime = glfwGetTime()*1000;
        moveFront =true;
    }

    if(key == GLFW_KEY_S && action == GLFW_PRESS && rotation == 0 && move == 0){
        //camera->moveFront(-1.0f);
        move = -1;
        prevTime = glfwGetTime()*1000;
        moveFront =true;
    }

    if(key == GLFW_KEY_D && action == GLFW_PRESS && rotation == 0 && move == 0){
        //camera->moveLeft(-1.0f);
        move = -1;
        prevTime = glfwGetTime()*1000;
        moveFront = false;
    }

    if(key == GLFW_KEY_A && action == GLFW_PRESS && rotation == 0 && move == 0) {
        //camera->moveLeft(1.0f);
        move = 1;
        prevTime = glfwGetTime()*1000;
        moveFront = false;
    }
    if(key == GLFW_KEY_Q && action == GLFW_PRESS && rotation == 0 && move == 0){
        rotation = 1;
        prevTime = glfwGetTime()*1000;
    }
    if(key == GLFW_KEY_E && action == GLFW_PRESS && rotation == 0){
        rotation = -1;
        prevTime = glfwGetTime()*1000;
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

static void cursor_position_callback(GLFWwindow* /*window*/, double /*xpos*/, double /*ypos*/)
{
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    window_width  = width;
    window_height = height;
    int frame_width = 0;
    int frame_height = 0;
    glfwGetFramebufferSize(window,&frame_width,&frame_height);
    glViewport(0, 0, frame_width, frame_height);
    PMatrix = glm::perspective(glm::radians(70.0f),static_cast<float>(window_width)/static_cast<float>(window_height),0.25f,100.f);
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
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Projet_Quentin_Lebon", nullptr, nullptr);
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
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Default proj matrix
    PMatrix = glm::perspective(glm::radians(70.0f),static_cast<float>(window_width)/static_cast<float>(window_height),0.25f,100.f);

    //For 3D
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    map = new Map("assets/map1");
    player = map->getPlayer();
    //exit(0);
    ShadersManager& shadersMana = map->getShadersManager();


    float phi_cam = 0.f;
    int cam_x = player->getMapX();
    int cam_z = player->getMapY();
    if(cam_z+1 >= map->getHeight()) phi_cam = 180.f;
    else if(cam_z == 0) phi_cam = 0.0f;
    else if(cam_x+1 >= map->getWidth()) phi_cam = -90.0f;
    else if(cam_x == 0) phi_cam = 90.0f;
    camera = new FreeflyCamera(glm::vec3(cam_x+1,0.5,cam_z),phi_cam);


        //float rotate = 0.f;
    // Loop until the user closes the window

    while (!glfwWindowShouldClose(window)) {
        //IO
        if(rotation != 0){
            double rotate_angle = (((glfwGetTime()*1000) - prevTime)*90)/900; //we compute the rotation needed to go to 90 degree in function of the elapsed time
            doneRotation += rotate_angle;
            doneRotation_real += rotate_angle;
            doneRotation = glm::clamp(doneRotation,0.0f,90.0f); //we clamp the value at 90 to be sure to have a 90 degres rotation
            if(doneRotation == 90){
                rotate_angle = -(doneRotation_real - rotate_angle)+90;//We recompute the angle to do our finale rotation and be at a cumulative rotation of 90 degree of the camera
                camera->rotateLeft(rotate_angle*rotation);// oriented roation
                doneRotation = 0;
                doneRotation_real = 0;
                rotation = 0;
            }else{
                camera->rotateLeft(rotate_angle*rotation);
            }
        }

        //Exclaty the same as for the rotation
        if(move != 0){
            double move_distance = ((glfwGetTime()*1000) - prevTime)/1200;
            doneMove += move_distance;
            doneMove_real += move_distance;
            doneMove = glm::clamp(doneMove,0.0f,1.0f);
            if(doneMove == 1 ){
                move_distance = -(doneMove_real - move_distance)+1;
                if(moveFront == true) {
                    camera->moveFront(move_distance * move);
                }
                else camera->moveLeft(move_distance*move);
                doneMove = 0;
                doneMove_real = 0;
                move = 0;
            }else{
                if(moveFront == true)camera->moveFront(move_distance*move);
                else camera->moveLeft(move_distance*move);
            }
            player->setRealX(camera->getPosition().x);
            player->setRealZ(camera->getPosition().z);
        }

        glClearColor(0.0f, 0.0f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        VMatrix = camera->getViewMatrix();

        glUniformMatrix4fv(shadersMana.getPMatrix(),1,GL_FALSE,glm::value_ptr(PMatrix));
        glUniformMatrix4fv(shadersMana.getVMatrix(),1,GL_FALSE,glm::value_ptr(VMatrix));


        glm::vec3 lightPos = camera->getPosition();
        glm::vec3 lightIntensity = glm::vec3(1);

        glUniform3fv(shadersMana.getLightPosVs(),1,glm::value_ptr(glm::vec3(VMatrix*glm::vec4(lightPos,1.0f))));
        glUniform3fv(shadersMana.getLightIntensity(),1,glm::value_ptr(lightIntensity));

        map->draw();

        //Swap front and back buffers
        glfwSwapBuffers(window);
        //Poll for and process events
        glfwPollEvents();
    }
    delete camera;
    glUseProgram(0);
}