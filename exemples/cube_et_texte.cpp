#include <GL/glut.h>

int width  = 800;
int height = 600;

void DrawString(float x, float y, const char* str)
{
    glRasterPos2f(x, y);

    while (*str)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str++);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //----------------------------
    // Perspective Projection
    //----------------------------
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        45.0,
        (double)width / height,
        0.1,
        100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        3,3,3,
        0,0,0,
        0,1,0);

    glColor3f(0,1,1);
    glutSolidTeapot(1.0);

    //----------------------------
    // Orthographic Overlay
    //----------------------------
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(0,width,0,height,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    glColor3f(1,1,0);

    DrawString(
        10,
        height-20,
        "OpenGL Fixed Pipeline Example");

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    width = w;
    height = h;

    glViewport(0,0,w,h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH);

    glutInitWindowSize(width, height);

    glutCreateWindow(
        "Perspective + Orthographic");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

    glutMainLoop();

    return 0;
}
