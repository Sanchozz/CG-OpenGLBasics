//internal includes
#include "common.h"
#include "ShaderProgram.h"

//External dependencies
#define GLFW_DLL
//#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <random>
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

static const GLsizei WIDTH = 640, HEIGHT = 480; //размеры окна

GLuint squareVBO;
GLuint squareVAO;
GLuint boxVBO;
GLuint boxVAO;
GLuint triangleVBO;
GLuint triangleVAO;
GLuint mirrorVBO;
GLuint mirrorVAO;

int initGL()
{
    int res = 0;
    //грузим функции opengl через glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "Vendor: "   << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: "  << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: "     << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return 0;
}

void genSquareBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;
    GLuint colorLocation = 1;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW); GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                    GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                        GL_CHECK_ERRORS;

    // glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);                                           GL_CHECK_ERRORS;
    glEnableVertexAttribArray(vertexLocation);                                                     GL_CHECK_ERRORS;
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(colorLocation); 
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));                           GL_CHECK_ERRORS;

    glBindVertexArray(0);
}

void genBoxBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;
    GLuint colorLocation = 1;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);                       GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                   GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                       GL_CHECK_ERRORS;

    glEnableVertexAttribArray(vertexLocation);                                    GL_CHECK_ERRORS;
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(colorLocation); 
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));                           GL_CHECK_ERRORS;

    glBindVertexArray(0);
}

void genTriangleBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;
    GLuint colorLocation = 1;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);                       GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                   GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                       GL_CHECK_ERRORS;

    glEnableVertexAttribArray(vertexLocation);                                    GL_CHECK_ERRORS;
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(colorLocation); 
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));                           GL_CHECK_ERRORS;

    glBindVertexArray(0);
}

void drawScene(GLFWwindow *window, ShaderProgram &program, glm::mat4 view, glm::mat4 projection, bool isReflect)
{
    glm::mat4 model(1.0f);
    program.StartUseShader();                           GL_CHECK_ERRORS;

        // очистка и заполнение экрана цветом
        //
        if (isReflect) {
            
        }

        // draw call
        //

        glBindVertexArray(squareVAO);                                            GL_CHECK_ERRORS;
        
        GLfloat cur_time = glfwGetTime();

        program.SetUniform("g_view", view);
        program.SetUniform("g_projection", projection);

        for (int i = 0; i < 6; i++) {
            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(60.0f * i) + glm::radians(cur_time) * 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, -glm::radians(cur_time) * 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));
            program.SetUniform("g_model", model);
            glDrawArrays(GL_TRIANGLES, 6 * i, 6 * (i + 1));
        }

        glBindVertexArray(boxVAO);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f)); //DELETE
        model = glm::rotate(model, (GLfloat) glm::radians(cur_time) * 50.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        program.SetUniform("g_model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(triangleVAO);

        for (int i = 0; i < 6; i++) {
            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(30.0f) + glm::radians(60.0f * i) - glm::radians(cur_time) * 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, glm::vec3(3.5f, 2.0f, 0.0f));
            model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(cur_time) * 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));
            program.SetUniform("g_model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        program.SetUniform("g_model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        program.StopUseShader();
}

void drawMirror(GLFWwindow *window, ShaderProgram &program, glm::mat4 view, glm::mat4 projection)
{
    glm::mat4 model(1.0f);
    program.StartUseShader();
    
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear     (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glClearDepth(0.0); 
        glDepthFunc(GL_ALWAYS);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glBindVertexArray(mirrorVAO);
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        program.SetUniform("g_view", view);
        program.SetUniform("g_projection", projection);
        program.SetUniform("g_model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDepthFunc(GL_LESS);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    program.StopUseShader();
}


int main(int argc, char** argv)
{
    if(!glfwInit())
    return -1;

    //запрашиваем контекст opengl версии 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

    GLFWwindow*  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL basic sample", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if(initGL() != 0) 
        return -1;

  //Reset any OpenGL errors which could be present for some reason
    GLenum gl_error = glGetError();
    while (gl_error != GL_NO_ERROR)
        gl_error = glGetError();

    //создание шейдерной программы из двух файлов с исходниками шейдеров
    //используется класс-обертка ShaderProgram
    std::unordered_map<GLenum, std::string> shaders;
    shaders[GL_VERTEX_SHADER]   = "vertex.glsl";
    shaders[GL_FRAGMENT_SHADER] = "fragment.glsl";
    ShaderProgram program(shaders); GL_CHECK_ERRORS;

    std::unordered_map<GLenum, std::string> shaders_mirror;
    shaders_mirror[GL_VERTEX_SHADER] = "vertex_mirror.glsl";
    shaders_mirror[GL_FRAGMENT_SHADER] = "fragment_mirror.glsl";
    ShaderProgram program_mirror(shaders_mirror); GL_CHECK_ERRORS;

    glfwSwapInterval(1); // force 60 frames per second
  
    //Создаем и загружаем геометрию поверхности
    //

    GLfloat mirrorSquarePos[] = 
    {
        // Первый треугольник
        0.5f,  0.0f, 0.5f, 1.0f, 1.0f, 1.0f,  // Верхний правый угол
        0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f,// Нижний правый угол
        -0.5f,  0.0f, 0.5f, 1.0f, 1.0f, 1.0f, 
        // Второй треугольник
        0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f,// Нижний правый угол
        -0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f,  // Нижний левый угол
        -0.5f,  0.0f, 0.5f, 1.0f, 1.0f, 1.0f,// Верхний левый угол
    };

    GLfloat trianglePos[] = 
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Left  
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// Right 
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// Top   
    };

    GLfloat squarePos[] =
    {
        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Верхний правый угол
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Нижний правый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Нижний правый угол
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Верхний левый угол

        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Верхний правый угол
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// Нижний правый угол
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// Нижний правый угол
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Верхний левый угол

        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Верхний правый угол
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// Нижний правый угол
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// Нижний правый угол
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Верхний левый угол

        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  // Верхний правый угол
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,// Нижний правый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,// Нижний правый угол
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // Верхний левый угол


        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // Верхний правый угол
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,// Нижний правый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,// Нижний правый угол
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // Верхний левый угол


        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 1.0f, 0.6275f, 0.0f,  // Верхний правый угол
        0.5f, -0.5f, 0.0f, 1.0f, 0.6275f, 0.0f,// Нижний правый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 0.6275f, 0.0f,
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 1.0f, 0.6275f, 0.0f,// Нижний правый угол
        -0.5f, -0.5f, 0.0f, 1.0f, 0.6275f, 0.0f,  // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 0.6275f, 0.0f, // Верхний левый угол


    };

    GLfloat boxPos[] =
    {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 0.6275f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.6275f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.6275f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.6275f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.6275f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.6275f, 0.0f,
    };


    glEnable(GL_DEPTH_TEST);

    genSquareBuf(squareVBO, squareVAO, squarePos, sizeof(squarePos));
    genBoxBuf(boxVBO, boxVAO, boxPos, sizeof(boxPos));
    genBoxBuf(triangleVBO, triangleVAO, trianglePos, sizeof(trianglePos));
    genSquareBuf(mirrorVBO, mirrorVAO, mirrorSquarePos, sizeof(mirrorSquarePos));


    //цикл обработки сообщений и отрисовки сцены каждый кадр
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //очищаем экран каждый кадр
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);               GL_CHECK_ERRORS;
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
        glm::mat4 model(1.0f);

        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
        view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 ref(1.0f);
        ref[1][1] = -1.0f;

        glm::mat4 reflected_view = view * ref;

        glm::mat4 projection(1.0f);
        projection = glm::perspective(45.0f, ((GLfloat) WIDTH) / HEIGHT, 0.1f, 100.0f);

        drawMirror(window, program_mirror, view, projection);
        drawScene(window, program, reflected_view, projection, true);
        glClearDepth(1.0f);
        drawScene(window, program, view, projection, false);
        
        
        glBindVertexArray(0);
        glfwSwapBuffers(window); 
    }

    //очищаем vboи vao перед закрытием программы
  //
    glDeleteVertexArrays(1, &squareVAO);
    glDeleteBuffers(1,      &squareVBO);

    glDeleteVertexArrays(1, &boxVAO);
    glDeleteBuffers(1,      &boxVBO);

    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1,      &triangleVBO);

    glDeleteVertexArrays(1, &mirrorVAO);
    glDeleteBuffers(1,      &mirrorVBO);

    glfwTerminate();
    return 0;
}
