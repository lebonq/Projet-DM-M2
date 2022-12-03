#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

int window_width  = 1280;
int window_height = 720;

static void key_callback(GLFWwindow* /*window*/, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)
{
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

static void size_callback(GLFWwindow* /*window*/, int width, int height)
{
    window_width  = width;
    window_height = height;
}

void draw_triangle(){

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
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "TP1_EXO2", nullptr, nullptr);
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

    //Bind Shaders
    glimac::Program program = glimac::loadProgram("/home/lebonq/Documents/Synthese-Image/GLImac-Template/bin/Debug/TP1/shaders/triangle.vs.glsl","/home/lebonq/Documents/Synthese-Image/GLImac-Template/bin/Debug/TP1/shaders/triangle.fs.glsl");
    program.use();

    const GLuint VERTEX_ATTR_POSITION = 3;
    const GLuint VERTEX_ATTR_COLOR = 8;

    /******************Init phase for triangle*****************************/
    GLuint vbo,vao; //create the VBO on cpu side
    glGenBuffers(1, &vbo);//Create 1 VBO on GPU side
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);//set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);//set the position for the vao
    glBindBuffer(GL_ARRAY_BUFFER,vbo);// bind le vbo sur GL ARRAY BUFFER so vertex attributes
    //Create coords of triangle

    GLfloat vertices[] = { -0.5f,-0.5f,1.f,0.f,0.f,
                            0.5f,-0.5f,0.f,1.f,0.f,
                            0.0f, 0.5f,0.f,0.f,1.f };//Our vertices attributes

    glBufferData(GL_ARRAY_BUFFER, 15*sizeof(GLfloat), vertices, GL_STATIC_DRAW);//Send data to GPU memory
    glVertexAttribPointer(VERTEX_ATTR_POSITION,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),0);//Say to the gpu how to use the VBO to draw position
    glVertexAttribPointer(VERTEX_ATTR_COLOR,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(2*sizeof(GLfloat)));//Say to the gpu how to use the VBO to draw color
    glBindBuffer(GL_ARRAY_BUFFER,0);//Un-bind our VBO from the arra_buffer
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        //####### Render Phase ###########
        draw_triangle();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
        //################################
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);

    //glfwTerminate();
    return 0;
}