

// #include <GL/glew.h>
// #include <GL/glut.h>

// #include <glew/glew.h>

#include <iostream>
#include <freeglut/GL/freeglut.h>


void RenderScenceCB(){
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

/**
 * 主函�?
 */
int main(int argc, char ** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");

    glutDisplayFunc(RenderScenceCB);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}
