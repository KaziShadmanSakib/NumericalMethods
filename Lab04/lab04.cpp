#include<GL/glut.h>
#define WIDTH 640
#define HEIGHT 480
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include<bits/stdc++.h>

#define n 8

double x[] = {-300.00, -150.00, -50.00, 0.00, 50.00, 150.00, 230.00, 300.00};
double fx[] = {-130.00, -100.00, -120.00, 130.00, -100.00, -50.00, 120.00, -100.00};
double c[n], b[n], d[n];

void doMatrix(void){

    double A[50][50] = {0};
    double x[] = {-300.00, -150.00, -50.00, 0.00, 50.00, 150.00, 230.00, 300.00};
    double fx[] = {-130.00, -100.00, -120.00, 130.00, -100.00, -50.00, 120.00, -100.00};
    double b[50];

    int idx = 0;
    int row = 0;

    //2n
    for(int i=0;i<n;i++){
        int j = (i)*3;
        int prev = j;
        A[row][j++] = x[idx] * x[idx];
        A[row][j++] = x[idx];
        A[row][j++] = 1;
        row++;
        j = prev;
        idx++;

        A[row][j++] = x[idx] * x[idx];
        A[row][j++] = x[idx];
        A[row][j++] = 1;
        row++;
    }


    //n-2
    int j=0;
    for(int i=1;i<n-1;i++){
        A[2*(n-1)+i][j] = 2*x[i];
        A[2*(n-1)+i][j+1] = 1;
        A[2*(n-1)+i][j+2] = 0;
        A[2*(n-1)+i][j+3] = -2*x[i];
        A[2*(n-1)+i][j+4] = -1;
        A[2*(n-1)+i][j+5] = 0;
        j+=3;
    }

    A[3*(n-1)][0] = 1;

    for(int i=0;i<=3*(n-1);i++){
        std::cout << "row " << i << ": ";
        for(int j=0;j<=3*(n-1)+2;j++){
            std::cout<< A[i][j] << "    ";
        }
        std::cout<< std::endl;
    }

    for(int i=0;i<(3*(n-1)-n); i++){
        fx[i+n] = 0;
    }

    for(int i=0;i<3*(n);i++){
        std::cout<< fx[i] << std::endl;
    }
}


static void reShape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2 - 1, -HEIGHT/2, HEIGHT/2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


static void display(void) {
    float X, Y;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // plotting the curve
    glPushMatrix();
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3ub(255, 100, 255);
    for(int i=0; i<n; i++){
       glVertex2f(x[i], fx[i]);
    }
    glEnd();

    glPointSize(1);

    glPushMatrix();
    glColor3ub(128, 128, 128);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH/2, 0);
    glVertex2i(WIDTH/2, 0);
    glVertex2i(0, -HEIGHT/2);
    glVertex2i(0, HEIGHT/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POINTS);
    for(int i=0;i<n-1;i++){
        glColor3ub(255-i*52, i*52, 0);
        X = x[i];
        for(int j=0;j<1000;j++){
            X+= (x[i+1]-x[i])/1000.0;
            Y = fx[i] + b[i]*(X-x[i]) + c[i]*pow((X - x[i]), 2.0) + d[i]*pow((X-x[i]),3.0);
            glVertex2f(X, Y);
        }
    }

    glEnd();
    glPopMatrix();
    glFlush();
}

static void idle(void) {
    glutPostRedisplay();
}

static void myinit(void) {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_MATERIAL);
}

void spline(void){

    int i, j;
    float h[n], A[n+1], u[n+1], z[n+1];

    //step 1
    for(j=0;j<n;++j){
        h[j] = x[j+1] - x[j];
    }

    //step 2
    A[0] = A[n] = 0;
    for(j=1;j<n;++j){
        A[j] = 3 * (fx[j+1]- fx[j]) / h[j] - 3 * (fx[j] - fx[j-1]) / h[j-1];

    }

    //step 3
    u[0] = 0;
    z[0] = 0;

    //step 4
    for(i=1;i<n;++i){
        u[i] = h[i] / (2* (x[i+1] - x[i-1]) - h[i-1]* u[i-1]);
        z[i] = (A[i] - h[i-1] * z[i-1]) / (2 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1]);
    }

    //step 5
    z[n] = 0;
    c[n] = 0;

    //step 6
    for(j=n-1; j>=0; --j){
        c[j] = z[j] - u[j] * c[j+1];
        b[j] = (fx[j+1] - fx[j]) / h[j] - h[j] * (c[j+1] + 2 * c[j]) / 3;
        d[j] = (c[j+1] -c[j]) / (3*h[j]);
    }

    //step 7
    printf("%2s %8s %8s %8s %8s\n", "i", "ai", "bi", "ci", "di");
    for(i=0;i<n;++i){
        printf("%2d %8.2f %8.2f %8.2f %8.2f\n", i, fx[i], b[i], c[i], d[i]);
    }

}

int main(int argc, char* argv[]) {

    doMatrix();
    spline();

    float X,Y;
    for(int i=0;i<n-1;i++){
        glColor3ub(255-i*52, i*52, 0);
        X = x[i];
        for(int j=0;j<10;j++){
            X+= (x[i+1]-x[i])/10.0;
            Y = fx[i] + b[i]*(X-x[i]) + c[i]*pow((X - x[i]), 2.0) + d[i]*pow((X-x[i]),3.0);
            printf("%0.4f %0.4f\n", X,Y);
        }
    }
  
    // Displaying Graph
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Lab Assignment 4");
    myinit();
    glutReshapeFunc(reShape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}