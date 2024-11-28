#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


const int w_width = 760;
const int w_height = 750;

float x1 = 0, yc = 0, x2 = 0, y2 = 0;
int count = 0;
int r = 0;
int w1 = -1, w2 = -1;

int major_x,minor_y;
int x_ellipse,y_ellipse;

float w2_x1 = 0, w2_yc = 0, w2_x2 = 0, w2_y2 = 0;
int w2_count = 0;
int w2_r = 0;

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void drawPoints(int xcenter, int ycenter, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(xcenter + x, ycenter + y);
    glVertex2d(xcenter - x, ycenter + y);
    glVertex2d(xcenter + x, ycenter - y);
    glVertex2d(xcenter - x, ycenter - y);

    glVertex2d(xcenter + y, ycenter + x);
    glVertex2d(xcenter - y, ycenter + x);
    glVertex2d(xcenter + y, ycenter - x);
    glVertex2d(xcenter - y, ycenter - x);
    glEnd();
    glFlush();
}

void display1() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (count == 2) {
        r = sqrt(pow(x2 - x1, 2) + pow(y2 - yc, 2));

        int x = 0;
        int y = r;
        int d = 1 - r;

        glColor3d(1.0, 1.0, 1.0);
        drawPoints(x1, yc, x, y);

        glBegin(GL_LINES);
        glVertex2d(x1, yc);
        glVertex2d(x2, y2);
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

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(w_width - 140, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(w_width - 140, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    glFlush();
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (w2_count == 3) {
        glColor3d(1.0, 0.0, 0.0);

        float x = 0;
        float y = minor_y;

        float y_sqr = minor_y * minor_y;
        float x_sqr = major_x * major_x;
        float p1 = y_sqr - (x_sqr) * minor_y + (x_sqr)/4;

        float dx = 2 * (y_sqr) * x;
        float dy = 2 * (x_sqr) * y;

        
        while (dx < dy) {
            glBegin(GL_POINTS);
                glVertex2f(x_ellipse + x, y_ellipse + y);
                glVertex2f(x_ellipse - x, y_ellipse + y);
                glVertex2f(x_ellipse + x, y_ellipse - y);
                glVertex2f(x_ellipse - x, y_ellipse - y);
            glEnd();

            if (p1 < 0) {
                x = x + 1;
                dx = 2 * (y_sqr) * x;
                p1 = p1 + dx + (y_sqr);
            } else {
                x = x + 1;
                y = y - 1;
                dx = 2 * (y_sqr) * x;
                dy = 2 * (x_sqr) * y;
                p1 = p1 + dx - dy + (y_sqr);
            }
        }

        
        float p2 = (y_sqr) * (x + 0.5) * (x + 0.5) + (x_sqr) * (y - 1) * (y - 1) - (x_sqr) * (y_sqr);

        while (y > 0) {
            glBegin(GL_POINTS);
                glVertex2f(x_ellipse + x, y_ellipse + y);
                glVertex2f(x_ellipse - x, y_ellipse + y);
                glVertex2f(x_ellipse + x, y_ellipse - y);
                glVertex2f(x_ellipse - x, y_ellipse - y);
            glEnd();

            if (p2 > 0) {
                y = y - 1;
                dy = 2 * (x_sqr) * y;
                p2 = p2 - dy + (x_sqr);
            } else {
                x = x + 1;
                y = y - 1;
                dx = 2 * (y_sqr) * x;
                dy = 2 * (x_sqr) * y;
                p2 = p2 + dx - dy + (x_sqr);
            }
        }
    }

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(w_width - 140, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(w_width - 140, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w_width, 0.0, w_height);
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

void key(unsigned char k, int x, int y) {
    switch (k) {
        case 'q':
            glutDestroyWindow(w1);
            break;
        case 'w':
            glutDestroyWindow(w2);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    
    glutInitWindowPosition(0, 20);
    glutInitWindowSize(w_width, w_height);
    w1 = glutCreateWindow("Midpoint Circle Algorithm");
    glutDisplayFunc(display1);
    glutMouseFunc(mouse1);
    init();
    glutKeyboardFunc(key);

    
    glutInitWindowPosition(w_width+10, 20);
    glutInitWindowSize(w_width, w_height);
    w2 = glutCreateWindow("2nd Window - Ellipse");
    glutDisplayFunc(display2);
    glutMouseFunc(mouse2);
    init();
    glutKeyboardFunc(key);

    printf("%d", w1);
    printf("%d", w2);

    glutMainLoop();
    return 0;
}
