#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

const int w_width = 1500;
const int w_height = 750;

float x1 = 0, yc = 0, x2 = 0, y2 = 0;
int count = 0;
int w2_count = 0;
int r = 0;

int major_x, minor_y;
int x_ellipse, y_ellipse;

int subwindow1, subwindow2;

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void drawPoints(int xcenter, int ycenter, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xcenter + x, ycenter + y);
    glVertex2i(xcenter - x, ycenter + y);
    glVertex2i(xcenter + x, ycenter - y);
    glVertex2i(xcenter - x, ycenter - y);
    glVertex2i(xcenter + y, ycenter + x);
    glVertex2i(xcenter - y, ycenter + x);
    glVertex2i(xcenter + y, ycenter - x);
    glVertex2i(xcenter - y, ycenter - x);
    glEnd();
}

void display1() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (count == 2) {
        r = sqrt(pow(x2 - x1, 2) + pow(y2 - yc, 2));

        int x = 0;
        int y = r;
        int d = 1 - r;

        glColor3f(1.0, 0.0, 0.0);
        drawPoints(x1, yc, x, y);

        glBegin(GL_LINES);
        glVertex2i(x1, yc);
        glVertex2i(x2, y2);
        glEnd();

        while (x < y) {
            if (d < 0) {
                d = d + 2 * x + 3;
                x++;
            } else {
                d = d + 2 * (x - y) + 5;
                y--;
                x++;
            }
            drawPoints(x1, yc, x, y);
        }
    }

    glColor3f(1.0, 0.0, 0.0);
    renderBitmapString(10, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");

    glutSwapBuffers();
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    

    if (w2_count == 3) {
        glColor3f(0.0, 1.0, 0.0);

        float x = 0;
        float y = minor_y;
        float dx, dy, d1, d2;
        float a2 = major_x * major_x;
        float b2 = minor_y * minor_y;

        d1 = b2 - (a2 * minor_y) + (0.25 * a2);
        dx = 2 * b2 * x;
        dy = 2 * a2 * y;

        while (dx < dy) {
            glBegin(GL_POINTS);
            glVertex2i(x_ellipse + x, y_ellipse + y);
            glVertex2i(x_ellipse - x, y_ellipse + y);
            glVertex2i(x_ellipse + x, y_ellipse - y);
            glVertex2i(x_ellipse - x, y_ellipse - y);
            glEnd();

            if (d1 < 0) {
                x++;
                dx += 2 * b2;
                d1 += dx + b2;
            } else {
                x++;
                y--;
                dx += 2 * b2;
                dy -= 2 * a2;
                d1 += dx - dy + b2;
            }
        }

        d2 = b2 * ((x + 0.5) * (x + 0.5)) + a2 * ((y - 1) * (y - 1)) - a2 * b2;

        while (y >= 0) {
            glBegin(GL_POINTS);
            glVertex2i(x_ellipse + x, y_ellipse + y);
            glVertex2i(x_ellipse - x, y_ellipse + y);
            glVertex2i(x_ellipse + x, y_ellipse - y);
            glVertex2i(x_ellipse - x, y_ellipse - y);
            glEnd();

            if (d2 > 0) {
                y--;
                dy -= 2 * a2;
                d2 += a2 - dy;
            } else {
                y--;
                x++;
                dx += 2 * b2;
                dy -= 2 * a2;
                d2 += dx - dy + a2;
            }
        }
    }

    glColor3f(1.0, 0.0, 0.0);
    renderBitmapString(10,20, GLUT_BITMAP_HELVETICA_18, "500106034");

    glutSwapBuffers();
}

void displayMain() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glutSwapBuffers();
}

void init_1() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w_width/2, 0, w_height);
    glMatrixMode(GL_MODELVIEW);
}


void init_2() {
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w_width/2, 0, w_height);
    glMatrixMode(GL_MODELVIEW);
}

void mouse1(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (count == 2) {
            count = 0;
        }
        if (count == 0) {
            x1 = x;
            yc = w_height - y;
            count++;
        } else if (count == 1) {
            x2 = x;
            y2 = w_height - y;
            count++;
            printf("cirrcle x %d y %d \n", x2, y2);
        }
        glutPostRedisplay();
    }
}


void mouse2(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (w2_count == 3) {
            w2_count = 0;
        }
        if (w2_count == 0) {
            
            x_ellipse = x;
            y_ellipse = w_height - y;
            printf("Center of ellipse: x %d y %d \n", x, (w_height - y));
            w2_count++;


        } 
        else if (w2_count == 1) {
            


            major_x = abs(x - x_ellipse);
            printf("Major x %d \n", major_x);
            w2_count++;

        } 
        else if (w2_count == 2) {
            minor_y = abs((w_height - y) - y_ellipse);
            printf("Minor y %d \n", minor_y);
            w2_count++;


        }


        glutPostRedisplay();
    
    }
}

// void key(unsigned char k, int x, int y) {
//     switch (k) {
//         case 'q':
//             glutDestroyWindow(w1);
//             break;
//         case 'w':
//             glutDestroyWindow(w2);
//             break;
//         default:
//             break;
//     }
// }


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w_width, w_height);
    int mainWindow = glutCreateWindow("Main Window with Two Sub-Windows");
    
    // init();
    glutDisplayFunc(displayMain);

    subwindow1 = glutCreateSubWindow(mainWindow, 0, 0, w_width / 2, w_height);
    init_1();
    glutDisplayFunc(display1);
    glutMouseFunc(mouse1);

    subwindow2 = glutCreateSubWindow(mainWindow, w_width / 2, 0, w_width / 2, w_height);
    init_2();
    glutDisplayFunc(display2);
    glutMouseFunc(mouse2);

    glutMainLoop();

    return 0;
}