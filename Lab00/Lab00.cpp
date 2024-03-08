/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>

#define Width 800
#define Height 600

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

//important function
static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2-1, -Height/2, Height/2-1, -1, 1); //projection plane
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

//important function
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(0,255,0);
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2i(-Width/2,0);
    glVertex2i(Width/2,0);
    glVertex2i(0,-Height/2);
    glVertex2i(0,Height/2);
    glEnd();
    glPopMatrix();
    
    glColor3ub(255,0,0);
    glPushMatrix();
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(20,20);
    glVertex2i(-22,20);
    glVertex2i(10,11);
    glVertex2i(-11,11);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}



static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };


//important function
void myInit(void){
    glClearColor(0,0,1,1);

    glEnable(GL_COLOR_MATERIAL);

}
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(Width,Height);
    glutInitWindowPosition(10,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); //For RGB 24 bits, for RGBA 32 bits

    glutCreateWindow("Numerical Methods Lab 00");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    myInit();

    glutMainLoop();

    return EXIT_SUCCESS;
}
