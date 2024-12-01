#include <GL/glut.h>
#include <stdio.h>

const int w_width = 900;
const int w_height = 750;

float x_min, y_min, x_max, y_max; 
float x1, yc, x2, y2;
int count = 0;

bool outer_line = true;
bool inner_line = true;

void renderBitmapString(float x, float y, void *font, const char *string) 
{
    glRasterPos2f(x, y);

    while (*string){
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void Clipping(float x1, float yc, float x2, float y2) {
    float p[4], q[4];
    float u1 = 0.0, u2 = 1.0;
    float dx = x2 - x1;
    float dy = y2 - yc;
    
    
    p[0] = -dx; 
    q[0] = x1 - x_min;

    p[1] = dx;  
    q[1] = x_max - x1;

    p[2] = -dy; 
    q[2] = yc - y_min;

    p[3] = dy;  
    q[3] = y_max - yc;


    bool flag = true;

    
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            flag = false;
            break;
        }
        float r = q[i] / p[i];
        if (p[i] < 0) {

            if (r > u1){
                u1 = r;
            } 

        } 
        else if (p[i] > 0) {

            if (r < u2){
                u2 = r;
            }
        }
    }

    
    if (outer_line) {
        glColor3f(1.0, 0.0, 0.0);

        glBegin(GL_LINES);
        glVertex2f(x1, yc);
        glVertex2f(x2, y2);
        
        glEnd();
    }

    
    if (flag && u1 < u2 && inner_line) {
        float clipped_x1 = x1 + u1 * dx;
        float clipped_yc = yc + u1 * dy;
        float clipped_x2 = x1 + u2 * dx;
        float clipped_y2 = yc + u2 * dy;

        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(clipped_x1, clipped_yc);
        glVertex2f(clipped_x2, clipped_y2);
        glEnd();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    
    if (count >= 4)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x_min, y_min);
        glVertex2f(x_max, y_min);
        glVertex2f(x_max, y_max);
        glVertex2f(x_min, y_max);
        glEnd();

    }

    
    if (count == 6) {
        Clipping(x1, yc, x2, y2);
    }

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(790, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(800, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    renderBitmapString(0, w_height-15, GLUT_BITMAP_HELVETICA_18, "Step 1: First Draw a rectangle window by click 4 times on screen");
    renderBitmapString(0, w_height-35, GLUT_BITMAP_HELVETICA_18, "Step 2: Then draw the line by click 2 times on screen");
    renderBitmapString(0, w_height-55, GLUT_BITMAP_HELVETICA_18, "Step 3: if you click one more time then the line will disappear then follow step 2");
    
    renderBitmapString(0, w_height-75, GLUT_BITMAP_HELVETICA_18, "use 'q' for clip outer line and use 'w' for clip inner line");


    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w_width, 0.0, w_height);
}


void keyboard(unsigned char key, int x, int y) {

    bool flag = false;

    if (key == 'q'){
        outer_line = !outer_line;
        flag = true;
        glutPostRedisplay();
    } 
    
    else if (key == 'w'){
        inner_line = !inner_line;
        glutPostRedisplay();
    }

    // else if (key == 'w' && flag){

    // }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if (count < 4) {
            if (count == 0) {
                x_min = x_max = x;
                y_min = y_max = w_height - y;
            } else {
                float x_curr = x;
                float y_curr = w_height - y;

                if (x_curr < x_min){
                    x_min = x_curr;
                    }

                if (x_curr > x_max){
                    x_max = x_curr;
                    }

                if (y_curr < y_min){
                    y_min = y_curr;
                    }

                if (y_curr > y_max){
                    y_max = y_curr;
                    }

            }
            count++;
        } 
        
        else if (count == 4){
            x1 = x;
            yc = w_height - y;
            count++;
        } 
        
        else if (count == 5){
            x2 = x;
            y2 = w_height - y;
            count++;
            glutPostRedisplay();
        } 
        
        else if (count == 6){
            count = 4;
            
        }
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w_width, w_height);
    glutCreateWindow("Exp 9 : Liang_Barsky Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
