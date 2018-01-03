
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <glew/glew.h>
#include <freeglut/GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_glut_backend.h"
#include "ogldev_pipeline.h"
#include "ogldev_camera.h"

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

PersProjInfo gPersprojInfo;
Camera* pGameCamera = NULL;


const char * pVSFileName = "shaderC.vs";
const char * pFSFileName = "shaderT.fs";

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.1f;
    
    Pipeline p;
    // p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
    // p.WorldPos(sinf(Scale), 0.0f, 0.0f);
    // p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);
    p.Rotate(0.0f, Scale, 0.0f);
    p.WorldPos(0.0f, 0.0f, 5.0f);
    p.SetPerspectiveProj(gPersprojInfo);
    p.SetCamera(*pGameCamera);
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat * )p.GetWVPTrans());


    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}
static void KeyboardCB(unsigned char Key, int x, int y)
{
    switch (Key) {
        case 'q':
            exit(0);
    }
}

static void PassiveMouseCB(int x, int y)
{
    pGameCamera->OnMouse(x, y);
}

static void SpecialKeyboardCB(int Key, int x, int y){
    OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
    pGameCamera->OnKeyboard(OgldevKey);

}

static void InitGlutCallbacks(){
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
    glutKeyboardFunc(KeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
    glutSpecialFunc(SpecialKeyboardCB);
}

static void CreateVertexBuffer(){
    Vector3f Vertices[4];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.5773f);
    Vertices[1] = Vector3f(0.0f, -1.0f, -1.15475f);
    Vertices[2] = Vector3f(1.0f, -1.0f, 0.5773f);
    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer(){
    unsigned int Indices [] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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

    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    assert(gWVPLocation != 0xFFFFFFFF);
}

int main(int argc, char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(100,100);
    glutCreateWindow("11Transformations");

    InitGlutCallbacks();

    GLenum res = glewInit();
    if (res != GLEW_OK){
        fprintf(stderr, "ERROR: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    printf("GL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();

    CreateIndexBuffer();

	compileShaders();

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

    gPersprojInfo.FOV = 60.0f;
    gPersprojInfo.Height = WINDOW_HEIGHT;
    gPersprojInfo.Width= WINDOW_WIDTH;
    gPersprojInfo.zNear = 1.0f;
    gPersprojInfo.zFar = 100.0f;

    glutMainLoop();

    return 0;
}