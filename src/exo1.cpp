#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>

int window_width  = 1300;
int window_height = 1300;

int old_xpos = 0.f;
int old_ypos = 0.f;

glm::mat4 PMatrix,VMatrix,MMatrix;
FreeflyCamera camera;

static void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
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
}

static void mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/)
{
}

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double /*yoffset*/)
{
}

static void cursor_position_callback(GLFWwindow* /*window*/, double xpos, double ypos)
{
    camera.rotateLeft(-(old_xpos - xpos)/100);
    camera.rotateUp((old_ypos - ypos)/100);
    old_xpos = xpos;
    old_ypos = ypos;
}

static void size_callback(GLFWwindow* /*window*/, int width, int height)
{
    window_width  = width;
    window_height = height;
    PMatrix = glm::perspective(glm::radians(70.0f),float((window_width/window_height)),0.1f,100.f);
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

    glimac::Sphere earth(1,32,16);

    //Bind Shaders
    glimac::Program program = glimac::loadProgram("TP6/shaders/sphere3D.vs.glsl","TP6/shaders/tex3D.fs.glsl");
    program.use();

    std::unique_ptr<glimac::Image> earth_tex = glimac::loadImage("assets/EarthMap.jpg");

    //Generate texture
    GLuint tex_earth;
    glGenTextures(1,&tex_earth);
    glBindTexture(GL_TEXTURE_2D,tex_earth);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,earth_tex.get()->getWidth(),earth_tex.get()->getHeight(),0,GL_RGBA,GL_FLOAT,earth_tex.get()->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    std::unique_ptr<glimac::Image> moon_tex = glimac::loadImage("assets/MoonMap.jpg");

    //Generate texture
    GLuint tex_moon;
    glGenTextures(1,&tex_moon);
    glBindTexture(GL_TEXTURE_2D,tex_moon);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,moon_tex.get()->getWidth(),moon_tex.get()->getHeight(),0,GL_RGBA,GL_FLOAT,moon_tex.get()->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEX_COORDS = 2;

    //get our uniform vairable fromt the shader
    GLuint uMMatrix = glGetUniformLocation(program.getGLId(),"uMMatrix");
    GLuint uVMatrix = glGetUniformLocation(program.getGLId(),"uVMatrix");
    GLuint uPMatrix = glGetUniformLocation(program.getGLId(),"uPMatrix");
    GLuint tex_loc = glGetUniformLocation(program.getGLId(),"uTex_data");


    glEnable(GL_DEPTH_TEST);

    GLuint vbo,vao;
    glGenBuffers(1,&vbo);
    glGenVertexArrays(1,&vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,earth.getVertexCount()*sizeof(glimac::ShapeVertex),earth.getDataPointer(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);//Un-bind our VBO from the arra_buffer

    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);//set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);//set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);//set the position for the vao
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);//Say to the gpu how to use the VBO to draw position
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));//Say to the gpu how to use the VBO to draw color
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));//Say to the gpu how to use the VBO to draw color
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);


    float rotate = 0.f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        //Create or matrix for projecting OBJ
        PMatrix = glm::perspective(glm::radians(35.0f),float((window_width/window_height)),0.1f,100.f);

        MMatrix = glm::translate(glm::mat4(1), glm::vec3(0,0,-5));
        VMatrix = camera.getViewMatrix();

        glClearColor(0.0f, 0.0f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Earth render
        glBindTexture(GL_TEXTURE_2D,tex_earth);
        glUniform1i(tex_loc,0);
        MMatrix = glm::rotate(MMatrix, rotate/2, glm::vec3(0, 1, 0)); // Translation * Rotation
        glUniformMatrix4fv(uVMatrix,1,GL_FALSE,glm::value_ptr(VMatrix));
        glUniformMatrix4fv(uMMatrix,1,GL_FALSE,glm::value_ptr(MMatrix));
        glUniformMatrix4fv(uPMatrix,1,GL_FALSE,glm::value_ptr(PMatrix));
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,earth.getVertexCount());

        //Moon render
        glBindTexture(GL_TEXTURE_2D,tex_moon);
        glUniform1i(tex_loc,0);
        MMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
        MMatrix = glm::rotate(MMatrix, rotate, glm::vec3(0, 1, 0)); // Translation * Rotation
        MMatrix = glm::translate(MMatrix, glm::vec3(-2, 0, 0)); // Translation * Rotation * Translation
        MMatrix = glm::scale(MMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
        glUniformMatrix4fv(uMMatrix,1,GL_FALSE,glm::value_ptr(MMatrix));
        glUniformMatrix4fv(uVMatrix,1,GL_FALSE,glm::value_ptr(VMatrix));
        glUniformMatrix4fv(uPMatrix,1,GL_FALSE,glm::value_ptr(PMatrix));

        glDrawArrays(GL_TRIANGLES,0,earth.getVertexCount());
        glBindTexture(GL_TEXTURE_2D,0);
        glBindVertexArray(0);
        rotate += 0.05f;
        //Avoid overflow
        if(rotate/360 >= 1){
            rotate = 0.0f;
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}