#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float x1 = 0, yc = 0, x2 = 0, y2 = 0;
int count = 0;
int r = 0;

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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (count == 2) {
        
        r = sqrt(pow(x2 - x1, 2) + pow(y2 - yc, 2));
        
        
        int x = 0;
        int y = r;
        int d = 1 - r;
        
        glColor3d(1.0, 1.0, 1.0);
        drawPoints(x1, yc, x, y);

        glBegin(GL_LINES);
        glVertex2d(x1,yc);
        glVertex2d(x2,y2);
        glEnd();

        while (x < y){
            if (d < 0){
                d = d + 2 * x + 3;
                x++;
            }

            else{
                d = d + 2 * (x - y) + 5;
                y--;
                x++;
            }
            
            drawPoints(x1, yc, x, y);
        }
    }

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(800, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(800, 40, GLUT_BITMAP_HELVETICA_18, "500106034");


    glFlush();
}

void init(){
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

    glutCreateWindow("Midpoint Circle Algorithm");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
