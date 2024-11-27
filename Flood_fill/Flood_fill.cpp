#include <GL/glut.h>
#include <cmath>
#include <math.h>

float oldColor[3] = {1.0f, 1.0f, 1.0f};
float newColor[3] = {1.0f, 0.5f, 0.1f};
float outsideColor[3] = {0.0f, 0.0f, 1.0f};

int xk = 320;
int yk = 240;
int radius = 50;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void setPixelColor(int x, int y, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(int x, int y, float oldColor[3], float newColor[3]) {
    float currentColor[3];
    getPixelColor(x, y, currentColor);
    if (currentColor[0] == oldColor[0] && currentColor[1] == oldColor[1] && currentColor[2] == oldColor[2]) {
        setPixelColor(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void onMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int my_h = glutGet(GLUT_WINDOW_HEIGHT);
        int my_Y = my_h - y;

        int distanceFromCenterX = x - xk;
        int distanceFromCenterY = my_Y - yk;
        int actualDistance = sqrt(distanceFromCenterX * distanceFromCenterX + distanceFromCenterY * distanceFromCenterY);

        if (actualDistance <= radius) {
            floodFill(x, my_Y, oldColor, newColor);
        } else {
            setPixelColor(x, my_Y, outsideColor);
        }
    }
}

void draw_circle(int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2i(xk + x, yk + y);
        glVertex2i(xk - x, yk + y);
        glVertex2i(xk + x, yk - y);
        glVertex2i(xk - x, yk - y);
        glVertex2i(xk + y, yk + x);
        glVertex2i(xk - y, yk + x);
        glVertex2i(xk + y, yk - x);
        glVertex2i(xk - y, yk - x);

        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        x++;
    }

    glEnd();
    glFlush();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_circle(radius);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Coloring");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutMainLoop();

    return 0;
}