#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float x1 = 0, yc = 0, x2 = 0, y2 = 0, slope = 0.0;
int count = 0;

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (count == 2) {
    
    float dx = abs(x2 - x1);
    float dy = abs(y2 - yc);

    float m = dy/dx;
    
    float pk = 2 * dy - dx;
    
    float x = x1, y = yc;


    int x_inc,y_inc;
    
    if(x2>x1){
        x_inc = 1;
    }
    else{
        x_inc = -1;
    }

    if(y2>yc){
        y_inc = 1;
    }
    else{
        y_inc = -1;
    }

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    glVertex2f(x, y);

    if (m<1){

        for (int i = 0; i < dx; i++) {

            x += x_inc;

            if (pk < 0){
                pk += 2 * dy;
            }
            else{
                y += y_inc;
                pk += 2 * (dy - dx);
            }
            glVertex2f(x, y);
        }

    } 
    
    else{
        for (int i = 0; i < dy; i++){

            y += y_inc;
            if(pk < 0)
            {
                pk += 2 * dx;
            } 
            else {
                x += x_inc;
                pk += 2 * (dx - dy);
            }
            glVertex2f(x, y);
        }
    }


    }

    glEnd();


    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(800, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(800, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    if (count == 2) {
        slope = (y2 - yc) / (x2 - x1);

        char slopeString[50];

        sprintf(slopeString, "Slope: %.2f", slope);
        renderBitmapString(20, 760, GLUT_BITMAP_HELVETICA_18, slopeString);

        char coord1String[50], coord2String[50];
        sprintf(coord1String, "Point 1: (%.0f, %.0f)", x1, yc);
        sprintf(coord2String, "Point 2: (%.0f, %.0f)", x2, y2);

        renderBitmapString(x1, yc, GLUT_BITMAP_HELVETICA_18, coord1String);
        renderBitmapString(x2, y2, GLUT_BITMAP_HELVETICA_18, coord2String);
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (count == 2) {
            count = 0;
        }

        if (count == 0) {
            x1 = x;
            yc = 780 - y;
            count++;
        } else if (count == 1) {
            x2 = x;
            y2 = 780 - y;
            count++;
        }
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 920.0, 0.0, 780.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(920, 780);

    glutCreateWindow("Bresenham Line Algorithm");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
