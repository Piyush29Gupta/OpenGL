#include <GL/glut.h>
#include <stdio.h>

float x1 = 0, yc = 0, x2 = 0, y2 = 0, slope = 0.0;
int count = 0;

void renderBitmapString(float x, float y, void *font, const char *string) 
{
    glRasterPos2f(x, y);

    while (*string){
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT);
    
    if (count == 2){
        float dy, dx, step, x, y, k, x_each, y_each;

        dx = x2 - x1;
        dy = y2 - yc;

        if (dx != 0){
            slope = dy / dx;
        } 

        else{
            slope = 0.0;
        }
        
        if (abs(dx) > abs(dy)){
            step = abs(dx);
        } 
        else{
            step = abs(dy);
        }
        
        x_each = dx / step;
        y_each = dy / step;
        
        x = x1;
        y = yc;
        
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        
        for (k = 1; k <= step; k++) {
            x = x + x_each;
            y = y + y_each;
            glVertex2f(x, y);
        }
        
        glEnd();
        
    }

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(800, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(800, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    char slopeString[50];
    sprintf(slopeString, "Slope: %.2f", slope);
    renderBitmapString(20, 760, GLUT_BITMAP_HELVETICA_18, slopeString);


    if(count == 2){
    char coord1String[50], coord2String[50];
    sprintf(coord1String, "Point 1: (%.0f, %.0f)", x1, yc);
    sprintf(coord2String, "Point 2: (%.0f, %.0f)", x2, y2);
    
    renderBitmapString(x1, yc, GLUT_BITMAP_HELVETICA_18, coord1String);
    renderBitmapString(x2, y2, GLUT_BITMAP_HELVETICA_18, coord2String);
    // count = 0;
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(count == 2){
            count = 0;
        }

        if(count == 0) {
            x1 = x;
            yc = 780 - y;
            count++;
        } 
        else if(count == 1) {
            x2 = x;
            y2 = 780 - y;
            count++;
            
        }
        // else if(count == 2){
        //     count = 0;
        // }
        glutPostRedisplay();
    }
        
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 920.0, 0.0, 780.0);
}

int main(int argc, char ** argv) {
    int mode = GLUT_RGB | GLUT_SINGLE;

    glutInit(&argc, argv); 
    glutInitDisplayMode(mode);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(920, 780);

    glutCreateWindow("Day to Night Transition- Experiment - 2");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
