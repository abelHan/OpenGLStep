
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <glew/glew.h>
#include <freeglut/GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_math_3d.h"

GLuint VBO;
GLuint gScaleLocation;


const char * pVSFileName = "shader.vs";
const char * pFSFileName = "shader.fs";

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.01f;
    glUniform1f(gScaleLocation, sinf(Scale));

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void InitGlutCallbacks(){
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
}

static void CreateVertexBuffer(){
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.f, -1.f, 0.f);
    Vertices[1] = Vector3f(1.f, -1.f, 0.f);
    Vertices[2] = Vector3f(0.f, 1.f, 0.f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void AddCurShader(GLuint ShaderProgram, const char *pShaderText, GLenum ShaderType){
    GLuint ShaderObj = glCreateShader(ShaderType);
    if (ShaderObj == 0){
        fprintf(stderr,"ERROR: creating shader type %d\n", ShaderType);
        exit(1);
    }

    const char * p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0] = strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);

    GLint Success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &Success);
    if (!Success){
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "ERROR compiling shader type %d: '%s'\n",ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void compileShaders(){
    GLuint ShaderProgram = glCreateProgram();
    if (ShaderProgram == 0){
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

	string vs, fs;

    if (!ReadFile(pVSFileName, vs)){
        exit(1);
    }
    if (!ReadFile(pFSFileName, fs)){
        exit(1);
    }

    AddCurShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddCurShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = {0};

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (!Success){
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);

    gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");
    assert(gScaleLocation != 0xFFFFFFFF);
}

int main(int argc, char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(100,100);
    glutCreateWindow("05Uniform");

    InitGlutCallbacks();

    GLenum res = glewInit();
    if (res != GLEW_OK){
        fprintf(stderr, "ERROR: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    printf("GL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();

	compileShaders();

    glutMainLoop();

    return 0;
}