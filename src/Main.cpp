#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Program.hpp>
#include <glimac/Sphere.hpp>
#include "Map.hpp"
#include "ModelsManager.hpp"
#include "TextRenderer.hpp"

int window_width  = 1920;
int window_height = 1080;

glm::mat4 PMatrix, VMatrix, PMatrix_player_stats, PMatrix_message;

float size_square_message;
double big_message_start_time = 0.0;
bool big_message_start = false;

int   rotation          = 0;
float doneRotation      = 0;
float doneRotation_real = 0;

int    move          = 0;
bool   moveFront     = false;
float  doneMove      = 0;
float  doneMove_real = 0;
double prevTime;

Map*           map;
Player*        player;
FreeflyCamera* camera;
std::vector<ShadersManager*> shaders;

double update_time = 0.0;

int* player_life;
int* player_defense;
int* player_attack;
int* player_gold;
bool* player_isDead;
bool* player_isHit;
bool* gameFinished;

//Message to print
std::string* big_message;
bool* big_printMessage;
TextRenderer* textRenderer;

//Hit effect
double hit_start_time = 0.0;
bool   hit_start      = false;

static void initMap(GLFWwindow* window){

    //allow us to draw "Loading map" On the screen
    glClearColor(0.0f, 0.0f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window_width, window_height);
    glDisable(GL_DEPTH_TEST); // UI is flat no need to test depth
    textRenderer->updatePMatrix(glm::ortho(0.0f, static_cast<GLfloat>(window_width), 0.0f, static_cast<GLfloat>(window_height)));
    float size_text = textRenderer->getSizeText("LOADING MAP",1.f);
            // Drawing the actuel text in the middle of the screen
    textRenderer->renderText("LOADING MAP"
                             ,((window_width - size_text)/2.f)
                             ,static_cast<GLfloat>(window_height)/2.f
                             ,1.0f
                             ,glm::vec4(1.f, 1.f, 1.f,1.f));
    glEnable(GL_DEPTH_TEST); // UI is flat no need to test depth
    glfwSwapBuffers(window);

    //reload the map
    map    = new Map("assets/dungeon_1");

    player = map->getPlayer();
    camera = player->getCamera();

    player_life    = player->getLifePtr();
    player_attack  = player->getAttackPtr();
    player_defense = player->getDefensePtr();
    player_gold    = player->getGoldPtr();
    player_isDead = player->getDeadPtr();
    big_message = map->getStrMessagePtr();
    big_printMessage = map->getBoolMessagePtr();
    gameFinished = map->getGameFinishedPtr();
    player_isHit = map->getPlayerIsHitPtr();

    shaders.clear();
    shaders.push_back(map->getShadersManagerFacing());
    shaders.push_back(map->getShadersManagerStatic());

    update_time = glfwGetTime() * 1000; // init update time

}

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if(*player_isDead){

    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS && rotation == 0 && move == 0) {
        if (map->canItGoThere(static_cast<int>(player->getXLookAt()),static_cast<int>( player->getYLookAt()))) {
            move      = 1;
            prevTime  = glfwGetTime() * 1000;
            moveFront = true;
        }
    }

    else if (key == GLFW_KEY_S && action == GLFW_PRESS && rotation == 0 && move == 0) {
        if (map->canItGoThere(static_cast<int>(player->getXLookAt() - (player->getLookAtXValue() * 2)),static_cast<int>( player->getYLookAt() - (player->getLookAtYValue() * 2)))) {
            move      = -1;
            prevTime  = glfwGetTime() * 1000;
            moveFront = true;
        }
    }

    else if (key == GLFW_KEY_D && action == GLFW_PRESS && rotation == 0 && move == 0) {
        int x, y;
        // on determine sur quel composante le joueur se deplace
        if (abs(player->getLookAtXValue()) - 1 == 0) { // soit Y
            x = static_cast<int>(player->getXLookAt() - player->getLookAtXValue());
            y = static_cast<int>(player->getYLookAt() + player->getLookAtXValue());
        }
        else { // soit X
            x = static_cast<int>(player->getXLookAt() - player->getLookAtYValue());
            y = static_cast<int>(player->getYLookAt() - player->getLookAtYValue());
        }
        if (map->canItGoThere(x, y)) {
            move      = -1;
            prevTime  = glfwGetTime() * 1000;
            moveFront = false;
        }
    }

    else if (key == GLFW_KEY_A && action == GLFW_PRESS && rotation == 0 && move == 0) {
        int x, y;
        if (abs(player->getLookAtXValue()) - 1 == 0) {
            x = static_cast<int>(player->getXLookAt() - player->getLookAtXValue());
            y = static_cast<int>(player->getYLookAt() - player->getLookAtXValue());
        }
        else {
            x = static_cast<int>(player->getXLookAt() + player->getLookAtYValue());
            y = static_cast<int>(player->getYLookAt() - player->getLookAtYValue());
        }

        if (map->canItGoThere(x, y)) {
            move      = 1;
            prevTime  = glfwGetTime() * 1000;
            moveFront = false;
        }
    }
   else if (key == GLFW_KEY_Q && action == GLFW_PRESS && rotation == 0 && move == 0) {
        rotation = 1;
        prevTime = glfwGetTime() * 1000;
    }
    else if (key == GLFW_KEY_E && action == GLFW_PRESS && rotation == 0 && move == 0) {
        rotation = -1;
        prevTime = glfwGetTime() * 1000;
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        map->interact();
    }
    if( key == GLFW_KEY_R && action == GLFW_PRESS && *player_isDead){
        delete map;
        initMap(window);
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
    PMatrix             = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.25f, 100.f);
    size_square_message = static_cast<float>(glm::min(window_width, window_height));
    PMatrix_message      = glm::ortho(glm::abs(size_square_message - static_cast<float>(window_width)) / 2.0f, (glm::abs(size_square_message - static_cast<float>(window_width)) / 2.0f) + size_square_message, glm::abs(size_square_message - static_cast<float>(window_height)) / 2.0f, size_square_message);
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

    // Init FreeType for text rendering
    textRenderer = new TextRenderer(window_height, window_width);

    // Default proj matrix
    PMatrix              = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.25f, 100.f);
    PMatrix_player_stats = glm::ortho(0.0f, static_cast<float>(220), 0.0f, static_cast<float>(220));
    size_square_message  = static_cast<float>(glm::min(window_width, window_height));
    PMatrix_message      = glm::ortho(glm::abs(size_square_message - static_cast<float>(window_width)) / 2.0f, (glm::abs(size_square_message - static_cast<float>(window_width)) / 2.0f) + size_square_message, glm::abs(size_square_message - static_cast<float>(window_height)) / 2.0f, size_square_message);

    // For 3D
    glEnable(GL_DEPTH_TEST);
    // for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float frequency = 20.0f; // shaking frequency

    initMap(window);
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        double current_time = glfwGetTime() * 1000;

        // IO
        if (rotation != 0) {
            double rotate_angle = ((current_time- prevTime) * 90) / 900; // we compute the rotation needed to go to 90 degree in function of the elapsed time
            doneRotation += static_cast<float>(rotate_angle);
            doneRotation_real += static_cast<float>(rotate_angle);
            doneRotation = glm::clamp(doneRotation, 0.0f, 90.0f); // we clamp the value at 90 to be sure to have a 90 degres rotation
            if (doneRotation == 90) {
                rotate_angle = -(doneRotation_real - rotate_angle) + 90; // We recompute the angle to do our finale rotation and be at a cumulative rotation of 90 degree of the camera
                player->rotateLeftCamera(rotate_angle * rotation);       // oriented roation
                doneRotation      = 0;
                doneRotation_real = 0;
                rotation          = 0;
            }
            else {
                player->rotateLeftCamera(rotate_angle * rotation);
            }
        }

        // Exclaty the same as for the rotation
        if (move != 0) {
            double move_distance = (current_time - prevTime) / 1200;
            doneMove += static_cast<float>(move_distance);
            doneMove_real += static_cast<float>(move_distance);
            doneMove = glm::clamp(doneMove, 0.0f, 1.0f);
            if (doneMove == 1) {
                float move_distancef = -(doneMove_real - static_cast<float>(move_distance)) + 1.0f;
                if (moveFront == true) {
                    player->moveToFrontCamera(move_distancef * static_cast<float>(move));
                }
                else {
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

        // update the state of map object if player not dead
        if(!*player_isDead)map->update(current_time);

        //get our time to compute the delta time and fade the big text
        if(*big_printMessage){
            *big_printMessage = false;
            big_message_start_time = current_time;
            big_message_start = true;
        }

        if(*player_isHit){
            *player_isHit = false;
            hit_start_time = current_time;
            hit_start = true;
        }



        glClearColor(0.0f, 0.0f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        VMatrix                  = camera->getViewMatrix();
        glm::vec3 lightPos       = camera->getPosition();
        glm::vec3 lightIntensity = glm::vec3(0.9f);

        if(hit_start) {
            if(current_time - hit_start_time > 500) {
                hit_start = false;
            }else {
                float intensity1 = static_cast<float>(glm::sin(current_time * frequency) * 0.03f);
                float intensity2 = static_cast<float>(glm::cos(current_time * frequency) * 0.03f);

                // Default proj matrix
                PMatrix = glm::perspective(glm::radians(70.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.25f, 100.f);
                // shake the projection matrix
                PMatrix = PMatrix * glm::mat4(1.0f + intensity1, 0.0f, 0.0f, 0.0f,
                                              0.0f, 1.0f + intensity2, 0.0f, 0.0f,
                                              0.0f, 0.0f, 1.0f, 0.0f,
                                              0.0f, 0.0f, 0.0f, 1.0f);
            }
        }

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
        if(hit_start || *player_isDead) glUniform1f(shader->getRedness(), .35f); //if player hit we make a red effect
        else glUniform1f(shader->getRedness(), 0.0f);
        map->drawStatic();
        // draw facing
        shader = shaders[0];
        shader->use();
        glUniformMatrix4fv(shader->getPMatrix(), 1, GL_FALSE, glm::value_ptr(PMatrix));
        glUniformMatrix4fv(shader->getVMatrix(), 1, GL_FALSE, glm::value_ptr(VMatrix));
        glUniform3fv(shader->getLightPosVs(), 1, glm::value_ptr(glm::vec3(VMatrix * glm::vec4(lightPos, 1.0f))));
        glUniform3fv(shader->getLightIntensity(), 1, glm::value_ptr(lightIntensity));
        if(hit_start || *player_isDead) glUniform1f(shader->getRedness(), .35f); //if player hit we make a red effect
        else glUniform1f(shader->getRedness(), 0.0f);
        map->drawFacing();
        //************************DRAW UI  ************************
        glDisable(GL_DEPTH_TEST); // UI is flat no need to test depth
        glViewport(window_width - 220, window_height - 220, 220, 220);
        textRenderer->updatePMatrix(PMatrix_player_stats);
        textRenderer->renderText("Life : " + std::to_string(*player_life), 0.0f, 0.0f, 0.20f, glm::vec4(0.5f, 0.8f, 0.2f,1.0f));
        textRenderer->renderText("Gold : " + std::to_string(*player_gold), 0.0f, 50.0f, 0.20F, glm::vec4(1.0f, 0.84f, 0.0f,1.0f));
        textRenderer->renderText("Attack : " + std::to_string(*player_attack), 0.0f, 100.0f, 0.20f, glm::vec4(1.0f, 0.3f, 0.3f,1.0f));
        textRenderer->renderText("Defense : " + std::to_string(*player_defense), 0.0f, 150.0f, 0.20f, glm::vec4(0.30f, 0.53f, 1.00f,1.0f));

        //Printing the big text with a fade effect
        if(big_message_start){
                        float text_opacity = 1.0f;
                        double time_elapsed = current_time-big_message_start_time;
                        //computing the fade effect and keep the text draw if the player is dead
                        if(time_elapsed < 500.0){
                            text_opacity = glm::clamp(static_cast<float>(time_elapsed)/500.f,0.f,1.f);
                        }
                        else if(time_elapsed > 1500.0 && !*player_isDead){
                            text_opacity = 1-glm::clamp(static_cast<float>(time_elapsed-1500)/500.f,0.f,1.f);
                        }
                        if(time_elapsed > 2000.0 && !*player_isDead){
                            big_message_start=false;
                        }

            glViewport(abs((static_cast<int>(size_square_message) - window_width)) / 2, 0, static_cast<int>(size_square_message), static_cast<int>(size_square_message));
            textRenderer->updatePMatrix(PMatrix_message);
            // Drawing the actuel text in the middle of the screen
            float size_text = textRenderer->getSizeText(*big_message,0.250f);
            textRenderer->renderText(*big_message
                                     , (glm::abs(size_square_message - static_cast<float>(window_width)) / 2.f)  + ((size_square_message - size_text)/2.f)
                                     , (glm::abs(size_square_message - static_cast<float>(window_height)) / 2.f) + (size_square_message/1.15f)
                                     , .250f
                                     , glm::vec4(1.f, 1.f, 1.f,text_opacity));
        }
        glEnable(GL_DEPTH_TEST);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    delete map;
    glUseProgram(0);
}