//internal includes
#include "common.h"
#include "ShaderProgram.h"
#include "buffer.h"
#include "texture.h"

//External dependencies
#define GLFW_DLL
#define STB_IMAGE_IMPLEMENTATION
//#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <random>
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>

static const GLsizei WIDTH = 640, HEIGHT = 480; //размеры окна

int curScene = 2;

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

void drawScene(GLFWwindow *window, ShaderProgram &program, ShaderProgram &program_texture, glm::mat4 view, glm::mat4 projection, GLuint texture)
{
    glm::mat4 model(1.0f);
    program.StartUseShader();                           GL_CHECK_ERRORS;

        GLfloat cur_time = glfwGetTime();

        program.SetUniform("g_view", view);
        program.SetUniform("g_projection", projection);

        

        glBindVertexArray(triangleVAO);

        for (int i = 0; i < 6; i++) {
            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(30.0f) + glm::radians(60.0f * i) - glm::radians(cur_time) * 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, glm::vec3(3.5f, 2.0f, 0.0f));
            model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(cur_time) * 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));
            program.SetUniform("g_model", model);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glBindVertexArray(squareVAO); GL_CHECK_ERRORS;
        for (int i = 0; i < 6; i++) {
            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(60.0f * i) + glm::radians(cur_time) * 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, -glm::radians(cur_time) * 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));
            program.SetUniform("g_model", model);
            //program.SetUniform("outTexture", 0);
            glDrawArrays(GL_TRIANGLES, 6 * i, 6 * (i + 1));GL_CHECK_ERRORS;
        }

        program.StopUseShader();  GL_CHECK_ERRORS;



        program_texture.StartUseShader();

        glBindTexture(GL_TEXTURE_2D, ricardoTexture);
        glBindVertexArray(boxVAO);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f)); //DELETE
        model = glm::rotate(model, (GLfloat) glm::radians(cur_time) * 50.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        program_texture.SetUniform("g_view", view);
        program_texture.SetUniform("g_projection", projection);
        program_texture.SetUniform("g_model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        program_texture.StopUseShader();
}

void drawScene2(GLFWwindow *window, ShaderProgram &program, ShaderProgram &program_texture, glm::mat4 view, glm::mat4 projection, GLuint texture)
{

}

void drawMirror(GLFWwindow *window, ShaderProgram &program, glm::mat4 view, glm::mat4 projection, bool isColored)
{
    glm::mat4 model;
    program.StartUseShader();
        if (!isColored) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear     (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            glDisable(GL_DEPTH_TEST);
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

            glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
            glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
        }

        glBindVertexArray(mirrorVAO);
        model = glm::mat4(1.0f);GL_CHECK_ERRORS;
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        program.SetUniform("g_view", view);
        program.SetUniform("g_projection", projection);
        program.SetUniform("g_model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        if (!isColored) {
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            glEnable(GL_DEPTH_TEST);

            glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if stencil ==1 */
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        }

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

    std::unordered_map<GLenum, std::string> shaders_texture;
    shaders_texture[GL_VERTEX_SHADER] = "vertex_texture.glsl";
    shaders_texture[GL_FRAGMENT_SHADER] = "fragment_texture.glsl";
    ShaderProgram program_texture(shaders_texture); GL_CHECK_ERRORS;

    std::unordered_map<GLenum, std::string> shaders_skybox;
    shaders_skybox[GL_VERTEX_SHADER] = "vertex_skybox.glsl";
    shaders_skybox[GL_FRAGMENT_SHADER] = "fragment_skybox.glsl";
    ShaderProgram program_skybox(shaders_skybox); GL_CHECK_ERRORS;

    glfwSwapInterval(1); // force 60 frames per second
  
    //Создаем и загружаем геометрию поверхности
    //
    int tex_width, tex_height, nrChannels;
    unsigned char *data = stbi_load("../textures/ricardo.png", &tex_width, &tex_height, &nrChannels, STBI_rgb_alpha); 
    
    glGenTextures(1, &ricardoTexture);  
    glBindTexture(GL_TEXTURE_2D, ricardoTexture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    genSquareBuf(squareVBO, squareVAO, squarePos, sizeof(squarePos));
    genBoxBuf(boxVBO, boxVAO, boxPos, sizeof(boxPos));
    genTriangleBuf(triangleVBO, triangleVAO, trianglePos, sizeof(trianglePos));
    genMirrorBuf(mirrorVBO, mirrorVAO, mirrorSquarePos, sizeof(mirrorSquarePos));GL_CHECK_ERRORS;
    genSkyboxBuf(skyboxVBO, skyboxVAO, skyboxVertices, sizeof(skyboxVertices));GL_CHECK_ERRORS;

    unsigned int cubemapTexture = loadCubemap(faces);

    glEnable(GL_DEPTH_TEST);
    //цикл обработки сообщений и отрисовки сцены каждый кадр
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (curScene == 1) {
            glm::mat4 model(1.0f);

            glm::mat4 view(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, -0.5f, -8.0f));
            view = glm::rotate(view, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            glm::mat4 ref(1.0f);
            ref[1][1] = -1.0f;

            glm::mat4 reflected_view = view * ref;

            glm::mat4 projection(1.0f);
            projection = glm::perspective(45.0f, ((GLfloat) WIDTH) / HEIGHT, 0.1f, 100.0f);
            
            
            glEnable(GL_STENCIL_TEST);
            drawMirror(window, program_mirror, view, projection, false);GL_CHECK_ERRORS;
            drawScene(window, program, program_texture, reflected_view, projection, ricardoTexture);GL_CHECK_ERRORS;
            glDisable(GL_STENCIL_TEST);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);GL_CHECK_ERRORS;
            drawMirror(window, program_mirror, view, projection, true);GL_CHECK_ERRORS;
            glDisable(GL_BLEND);GL_CHECK_ERRORS;

            drawScene(window, program, program_texture, view, projection, ricardoTexture);
            
            glBindVertexArray(0);
        } else if (curScene == 2) {

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear     (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glDepthMask(GL_FALSE);
            
            program_skybox.StartUseShader();

            
            glm::mat4 model(1.0f);

            glm::mat4 view(1.0f);
            //view = glm::translate(view, glm::vec3(0.0f, -0.5f, -8.0f));
            //view = glm::rotate(view, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //view = glm::mat4(glm::mat3(view));

            
            glm::mat4 projection(1.0f);
            projection = glm::perspective(45.0f, ((GLfloat) WIDTH) / HEIGHT, 0.1f, 100.0f);
            glBindVertexArray(skyboxVAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            program_skybox.SetUniform("g_model", model);
            program_skybox.SetUniform("g_view", view);
            program_skybox.SetUniform("g_projection", projection);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
            program_skybox.StopUseShader();
            glDepthMask(GL_TRUE);
            glBindVertexArray(0);
        }
        glfwSwapBuffers(window); 
    }

    //очищаем vboи vao перед закрытием программы
  //
    cleanBuffers();

    glfwTerminate();
    return 0;
}
