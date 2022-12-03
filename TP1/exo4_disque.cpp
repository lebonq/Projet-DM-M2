#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <vector>

int window_width  = 1500;
int window_height = 1500;

struct Vertex2DColor
{
   glm::vec2 position;
   glm::vec3 color;

   Vertex2DColor(glm::vec2 p, glm::vec3 c){
    position = p;
    color = c;
   }
};

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
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "TP1_EXO3", nullptr, nullptr);
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

    int defCircle = 10000;
    float rayonCercle = 0.5f;

    float degrePerTrig = 360.0f/defCircle;
    float radianPerTrig = (degrePerTrig*M_PI)/180.0f;

    float pX = rayonCercle;
    float pY = 0.0f;

    std::vector<GLfloat> verticesCircles;
    std::vector<GLuint> indiceCircles;

    verticesCircles.push_back(0.0f);
    verticesCircles.push_back(0.0f);
    verticesCircles.push_back(0.0f);
    //Color
    verticesCircles.push_back(1.0f);
    verticesCircles.push_back(1.0f);
    verticesCircles.push_back(0.0f);

    int indice = 1;

    for(int i = 0; i <= defCircle;i++){
        indiceCircles.push_back(0);
        verticesCircles.push_back(pX);//First point
        indiceCircles.push_back(indice);
        indice++;
        verticesCircles.push_back(pY);
        indiceCircles.push_back(indice);
        indice++;
        verticesCircles.push_back(0.0f);
        
        if(i%2==0){
            verticesCircles.push_back(0.0f);
            verticesCircles.push_back(1.0f);
            verticesCircles.push_back(0.0f);
        }
        else{
            verticesCircles.push_back(0.0f);
            verticesCircles.push_back(0.0f);
            verticesCircles.push_back(1.0f);
        }
        float pXTemp = pX;
        float pYTemp = pY;

        pX = (pXTemp*cosf(radianPerTrig))-(pYTemp*sinf(radianPerTrig));

        pY = (pXTemp*sinf(radianPerTrig))+(pYTemp*cosf(radianPerTrig));

        indiceCircles.push_back(0);
        verticesCircles.push_back(pX);//Second point
        indiceCircles.push_back(indice);
        indice++;
        verticesCircles.push_back(pY);
        indiceCircles.push_back(indice);
        indice++;
        verticesCircles.push_back(0.0f);
        //Color
        if(i%2==0){
            verticesCircles.push_back(0.0f);
            verticesCircles.push_back(0.0f);
            verticesCircles.push_back(1.0f);
        }
        else{
            verticesCircles.push_back(0.0f);
            verticesCircles.push_back(1.0f);
            verticesCircles.push_back(0.0f);
        }
    }

        /******************Init phase for triangle*****************************/
    GLuint vbo,vao,ebo; //create the VBO on cpu side
    glGenBuffers(1, &vbo);//Create 1 VBO on GPU side
    glGenVertexArrays(1,&vao);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);// bind le vbo sur GL ARRAY BUFFER so vertex attributes
    glBufferData(GL_ARRAY_BUFFER, verticesCircles.size()*sizeof(GLfloat), verticesCircles.data(), GL_STATIC_DRAW);//Send data to GPU memory
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceCircles.size()*sizeof(GLuint), indiceCircles.data(), GL_STATIC_DRAW);//Send data to GPU memory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);//set the position for the vao
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);//set the position for the vao
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)0);//Say to the gpu how to use the VBO to draw position
    glVertexAttribPointer(VERTEX_ATTR_COLOR,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)(2*sizeof(GLfloat)));//Say to the gpu how to use the VBO to draw color
    glBindBuffer(GL_ARRAY_BUFFER,0);//Un-bind our VBO from the arra_buffer
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        //####### Render Phase ###########
        draw_triangle();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES,indice,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        //################################
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&ebo);

    //glfwTerminate();
    return 0;
}