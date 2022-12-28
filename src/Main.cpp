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
#include "TextRenderer.hpp"

int window_width  = 1920;
int window_height = 1080;

int old_xpos = 0.f;
int old_ypos = 0.f;

glm::mat4      PMatrix, VMatrix;
int            rotation          = 0;
float          doneRotation      = 0;
float          doneRotation_real = 0;

int    move          = 0;
bool   moveFront     = false;
float  doneMove      = 0;
float  doneMove_real = 0;
double prevTime;

Map*    map;
Player* player;
FreeflyCamera* camera;

double update_time = 0.0;

int* player_life;
int* player_defense;
int* player_attack;
int* player_gold;

float randomFloat() {
  std::srand(std::time(nullptr));
  float f = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
  f *=0.02f; // scale to 0.0 to 0.2
  f -=0.01f; // scale to -0.1 to 0.1
  return f;
}

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS && rotation == 0 && move == 0) {
        // camera->moveFront(1.0f);

        move      = 1;
        prevTime  = glfwGetTime() * 1000;
        moveFront = true;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS && rotation == 0 && move == 0) {
        // camera->moveFront(-1.0f);
        move      = -1;
        prevTime  = glfwGetTime() * 1000;
        moveFront = true;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS && rotation == 0 && move == 0) {
        // camera->moveLeft(-1.0f);
        move      = -1;
        prevTime  = glfwGetTime() * 1000;
        moveFront = false;
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS && rotation == 0 && move == 0) {
        // camera->moveLeft(1.0f);
        move      = 1;
        prevTime  = glfwGetTime() * 1000;
        moveFront = false;
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS && rotation == 0 && move == 0) {
        rotation = 1;
        prevTime = glfwGetTime() * 1000;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS && rotation == 0 && move == 0) {
        rotation = -1;
        prevTime = glfwGetTime() * 1000;
    }
    if( key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        map->interact();
    }
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

static void mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/)
{

}

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double /*yoffset*/)
{
}

static void cursor_position_callback(GLFWwindow* /*window*/, double /*xpos*/, double /*ypos*/)
{
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    window_width     = width;
    window_height    = height;
    int frame_width  = 0;
    int frame_height = 0;
    glfwGetFramebufferSize(window, &frame_width, &frame_height);
    glViewport(0, 0, frame_width, frame_height-200);
    PMatrix = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.25f, 100.f);
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
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //-200 for UI
    glViewport(0, 0, window_width, window_height-200);
    //Init FreeType for text rendering
    TextRenderer* textRenderer = new TextRenderer(window_height,window_width);


    // Default proj matrix
    PMatrix = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.25f, 100.f);

    // For 3D
    glEnable(GL_DEPTH_TEST);
    //for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    map    = new Map("assets/map1");
    player = map->getPlayer();
    camera = player->getCamera();
    // exit(0);

    player_life = map->getPlayerLifePtr();
    player_attack = map->getPlayerAttackPtr();
    player_defense = map->getPlayerDefensePtr();
    player_gold = map->getPlayerGoldPtr();

    std::vector<ShadersManager*> shaders;
    shaders.push_back(map->getShadersManagerFacing());
    shaders.push_back(map->getShadersManagerStatic());


    update_time = glfwGetTime() * 1000;//init update time
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // IO
        if (rotation != 0) {
            double rotate_angle = (((glfwGetTime() * 1000) - prevTime) * 90) / 900; // we compute the rotation needed to go to 90 degree in function of the elapsed time
            doneRotation += rotate_angle;
            doneRotation_real += rotate_angle;
            doneRotation = glm::clamp(doneRotation, 0.0f, 90.0f); // we clamp the value at 90 to be sure to have a 90 degres rotation
            if (doneRotation == 90) {
                rotate_angle = -(doneRotation_real - rotate_angle) + 90; // We recompute the angle to do our finale rotation and be at a cumulative rotation of 90 degree of the camera
                camera->rotateLeft(rotate_angle * rotation);             // oriented roation
                doneRotation      = 0;
                doneRotation_real = 0;
                rotation          = 0;
            }
            else {
                camera->rotateLeft(rotate_angle * rotation);
            }
        }

        // Exclaty the same as for the rotation
        if (move != 0) {
            double move_distance = ((glfwGetTime() * 1000) - prevTime) / 1200;
            doneMove += static_cast<float>(move_distance);
            doneMove_real += static_cast<float>(move_distance);
            doneMove = glm::clamp(doneMove, 0.0f, 1.0f);
            if (doneMove == 1) {
                float move_distancef = -(doneMove_real - static_cast<float>(move_distance)) + 1.0f;
                if (moveFront == true) {
                    player->moveToFrontCamera(move_distancef * static_cast<float>(move));
                }
                else{
                    player->moveToLeftCamera(move_distancef * static_cast<float>(move));
                }
                doneMove      = 0;
                doneMove_real = 0;
                move          = 0;
                player->updateMapPos();
            }
            else {
                if (moveFront == true)
                    player->moveToFrontCamera(static_cast<float>(move_distance) * static_cast<float>(move));
                else
                    player->moveToLeftCamera(static_cast<float>(move_distance) * static_cast<float>(move));
            }
        }

        //update the state of map object
        map->update(glfwGetTime() * 1000);

        glClearColor(0.0f, 0.0f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        VMatrix                  = camera->getViewMatrix();
        glm::vec3 lightPos       = camera->getPosition();
        glm::vec3 lightIntensity = glm::vec3(0.9);


        /*float frequency = 20.0f; // shaking frequency
        float time = glfwGetTime(); // current time

        float intensity1 = glm::sin(time * frequency) *0.03f+randomFloat();
        float intensity2 = glm::cos(time * frequency) * 0.03f+randomFloat();

        // Default proj matrix
        PMatrix = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.25f, 100.f);
        // shake the projection matrix
        PMatrix = PMatrix *  glm::mat4(1.0f+intensity1, 0.0f, 0.0f, 0.0f,
                                                    0.0f, 1.0f+intensity2, 0.0f, 0.0f,
                                                    0.0f, 0.0f, 1.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f);*/


        //************************DRAW GAME************************
        glViewport(0, 0, window_width, window_height);
        ShadersManager* shader;
        // draw static
        shader = shaders[1];
        shader->use();
        glUniformMatrix4fv(shader->getPMatrix(), 1, GL_FALSE, glm::value_ptr(PMatrix));
        glUniformMatrix4fv(shader->getVMatrix(), 1, GL_FALSE, glm::value_ptr(VMatrix));
        glUniform3fv(shader->getLightPosVs(), 1, glm::value_ptr(glm::vec3(VMatrix * glm::vec4(lightPos, 1.0f))));
        glUniform3fv(shader->getLightIntensity(), 1, glm::value_ptr(lightIntensity));
        map->drawStatic();
        // draw facing
        shader = shaders[0];
        shader->use();
        glUniformMatrix4fv(shader->getPMatrix(), 1, GL_FALSE, glm::value_ptr(PMatrix));
        glUniformMatrix4fv(shader->getVMatrix(), 1, GL_FALSE, glm::value_ptr(VMatrix));
        glUniform3fv(shader->getLightPosVs(), 1, glm::value_ptr(glm::vec3(VMatrix * glm::vec4(lightPos, 1.0f))));
        glUniform3fv(shader->getLightIntensity(), 1, glm::value_ptr(lightIntensity));
        map->drawFacing();
        //************************DRAW UI  ************************
        glDisable(GL_DEPTH_TEST); //UI is flat no need to test depth
        glViewport(0, window_height-200, window_width, 200);
        textRenderer->renderText("Life : " + std::to_string(*player_life), 0.0f, 0.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        textRenderer->renderText("Gold : " + std::to_string(*player_gold), 0.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        textRenderer->renderText("Attack : " + std::to_string(*player_attack), 0.0f, 100.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        textRenderer->renderText("Defense : " + std::to_string(*player_defense), 0.0f, 150.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        glEnable(GL_DEPTH_TEST);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    delete camera;
    glUseProgram(0);
}