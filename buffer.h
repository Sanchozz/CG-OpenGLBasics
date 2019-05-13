#include "common.h"
#include "ShaderProgram.h"

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

GLuint squareVBO;
GLuint squareVAO;
GLuint boxVBO;
GLuint boxVAO;
GLuint triangleVBO;
GLuint triangleVAO;
GLuint mirrorVBO;
GLuint mirrorVAO;
GLuint skyboxVBO;
GLuint skyboxVAO;
GLuint tetraVBO;
GLuint tetraVAO;

GLfloat mirrorSquarePos[] = 
    {
        // Первый треугольник
        0.5f,  0.0f, 0.5f,// 0.7f, 0.0f, 0.0f,  // Верхний правый угол
        0.5f, 0.0f, -0.5f,// 0.7f, 0.0f, 0.0f,// Нижний правый угол
        -0.5f,  0.0f, 0.5f,// 0.7f, 0.0f, 0.0f, 
        // Второй треугольник
        0.5f, 0.0f, -0.5f,// 0.7f, 0.0f, 0.0f,// Нижний правый угол
        -0.5f, 0.0f, -0.5f,// 0.7f, 0.0f, 0.0f,  // Нижний левый угол
        -0.5f,  0.0f, 0.5f, //0.7f, 0.0f, 0.0f,// Верхний левый угол
    };

    GLfloat trianglePos[] = 
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Left  
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// Right 
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// Top 

        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Left  
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Right 
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Top  
    };

    GLfloat squarePos[] =
    {
        // 1 Красно-зеленый
        // Первый треугольник
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Верхний правый угол
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Нижний правый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        // Второй треугольник
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Нижний правый угол
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Нижний левый угол
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Верхний левый угол

        //1 Красно-зеленый
        //Первый треугольник
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
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f ,0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f , 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f , 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f , 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f ,0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 0.6275f, 0.0f,0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.6275f, 0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.6275f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.6275f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.6275f, 0.0f,0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.6275f, 0.0f,0.0f, 1.0f,
    };


    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

GLfloat tetraPos[] =
{
    1.0f, 0.0f, -0.7071067811865475f,
    -1.0f, 0.0f, -0.7071067811865475f,
    0.0f, 1.0f, 0.7071067811865475f,

    0.0f, -1.0f, 0.7071067811865475f,
    1.0f, 0.0f, -0.7071067811865475f,
    -1.0f, 0.0f, -0.7071067811865475f,

    -1.0f, 0.0f, -0.7071067811865475f,
    0.0f, 1.0f, 0.7071067811865475f,
    0.0f, -1.0f, 0.7071067811865475f,

    1.0f, 0.0f, -0.7071067811865475f,
    0.0f, 1.0f, 0.7071067811865475f,
    0.0f, -1.0f, 0.7071067811865475f,
};

void genSquareBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;
    GLuint colorLocation = 1;
    GLuint textureLocation = 2;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW); GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                    GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                        GL_CHECK_ERRORS;

    // glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);                                           GL_CHECK_ERRORS;
    
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(vertexLocation);                                                     GL_CHECK_ERRORS;
    
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));  
    glEnableVertexAttribArray(colorLocation);                          GL_CHECK_ERRORS;
    
    //glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));   
    //glEnableVertexAttribArray(textureLocation); 

    glBindVertexArray(0);
}

void genMirrorBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
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
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);                   GL_CHECK_ERRORS;

    glBindVertexArray(0);
}

void genBoxBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;
    GLuint colorLocation = 1;
    GLuint textureLocation = 2;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);                       GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                   GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                       GL_CHECK_ERRORS;

    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(vertexLocation);  
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));       GL_CHECK_ERRORS;
    glEnableVertexAttribArray(colorLocation); 
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));   
    glEnableVertexAttribArray(textureLocation); 

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

void genSkyboxBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);                       GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                   GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                       GL_CHECK_ERRORS;

    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); 
    glEnableVertexAttribArray(vertexLocation);  

    glBindVertexArray(0);
}

void genTetraBuf(GLuint &vbo, GLuint &vao, GLfloat *pos, GLsizeiptr size)
{
    GLuint vertexLocation = 0;

    glGenBuffers(1, &vbo);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);                       GL_CHECK_ERRORS;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pos);

    glGenVertexArrays(1, &vao);                                                   GL_CHECK_ERRORS;
    glBindVertexArray(vao);                                                       GL_CHECK_ERRORS;

    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); 
    glEnableVertexAttribArray(vertexLocation);  

    glBindVertexArray(0);
}

void cleanBuffers()
{
    glDeleteVertexArrays(1, &squareVAO);
    glDeleteBuffers(1,      &squareVBO);

    glDeleteVertexArrays(1, &boxVAO);
    glDeleteBuffers(1,      &boxVBO);

    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1,      &triangleVBO);

    glDeleteVertexArrays(1, &mirrorVAO);
    glDeleteBuffers(1,      &mirrorVBO);

    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1,      &skyboxVBO);

    glDeleteVertexArrays(1, &tetraVAO);
    glDeleteBuffers(1,      &tetraVBO);
}