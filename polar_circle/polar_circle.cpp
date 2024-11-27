#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <cmath>

float x1 = 0, yc = 0, x2 = 0, y2 = 0;
int count = 0;
int r = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (count == 2) {
        
        glColor3d(1.0,1.0,1.0);
        r = sqrt(pow(x2 - x1, 2) + pow(y2 - yc, 2));

        glBegin(GL_POINTS);


        glVertex2d(x1, yc);

        for (int i = 0; i <= 360; i++) {
            float theta = 2.0 * 3.14 * i / 360;
            float dx = r * cosf(theta);
            float dy = r * sinf(theta);


            glVertex2d(x1 + dx, yc + dy);
        }

        glEnd();
        glFlush();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 920.0, 0.0, 780.0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (count == 2) {
            count = 0;
        }
        if (count == 0) {
            x1 = x;
            yc = 760 - y;
            count++;
        } else if (count == 1) {
            x2 = x;
            y2 = 760 - y;
            count++;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(920, 760);

    glutCreateWindow("Polar Circle Algorithm");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
