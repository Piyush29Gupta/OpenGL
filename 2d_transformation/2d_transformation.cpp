#include <GL/glut.h>
#include <cmath>
using namespace std;

const int w_width = 900;
const int w_height = 750;

float x_min, y_min, x_max, y_max;
float x1, yc, x2, y2;
int count = 0;

float translation[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

float rotation[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

float scaling[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

float shearing[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

float reflecting[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

float box[4][3];


float center_x = 0.0;
float center_y = 0.0;

void renderBitmapString(float x, float y, void *font, const char *string) 
{
    glRasterPos2f(x, y);

    while (*string){
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void initialize_matrix() {
    for (int i = 0; i < 3; i++){

        translation[i][i] = 1;
        
        rotation[i][i] = 1;
        
        scaling[i][i] = 1;
        
        shearing[i][i] = 1;

        reflecting[i][i] = 1;
    }
}

void multiply_matrix(float matrix[3][3]){

    float temp[4][3];
    
    for (int i = 0; i < 4; i++){

        temp[i][0] = box[i][0] * matrix[0][0] + box[i][1] * matrix[0][1] + box[i][2] * matrix[0][2];
        
        temp[i][1] = box[i][0] * matrix[1][0] + box[i][1] * matrix[1][1] + box[i][2] * matrix[1][2];
        
        temp[i][2] = box[i][0] * matrix[2][0] + box[i][1] * matrix[2][1] + box[i][2] * matrix[2][2];
    
    }

    for (int i = 0; i < 4; i++){

        box[i][0] = temp[i][0];
        
        box[i][1] = temp[i][1];
        
        box[i][2] = temp[i][2];
    }
}

void translate(float tx, float ty){


    translation[0][2] = tx;
    translation[1][2] = ty;

    multiply_matrix(translation);
}

void scale(float sx, float sy){
    translate(-center_x, -center_y);

    scaling[0][0] = sx;
    scaling[1][1] = sy;

    multiply_matrix(scaling);

    translate(center_x, center_y);
}

void rotate(float angle){
    translate(-center_x, -center_y);

    angle = angle * 3.14 / 360.0;

    rotation[0][0] = cos(angle);
    rotation[0][1] = -sin(angle);
    rotation[1][0] = sin(angle);
    rotation[1][1] = cos(angle);

    multiply_matrix(rotation);

    translate(center_x, center_y);
}

void shear(float shx, float shy) {
    translate(-center_x, -center_y);

    shearing[0][1] = shx;
    shearing[1][0] = shy;

    multiply_matrix(shearing);

    translate(center_x, center_y);
}

void reflect(float fx, float fy){
    
    translate(-center_x, -center_y);

    reflecting[0][0] = fx;
    reflecting[1][1] = fy;

    multiply_matrix(reflecting);

    translate(center_x,center_y);
}

void reset() {
    for (int i = 0; i < 4; i++) {
        box[i][0] = 0;
        box[i][1] = 0;
        box[i][2] = 1;
    }

    center_x = center_y = 0;
    count = 0;

    initialize_matrix();
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (count >= 4) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(box[0][0], box[0][1]);
        glVertex2f(box[1][0], box[1][1]);
        glVertex2f(box[2][0], box[2][1]);
        glVertex2f(box[3][0], box[3][1]);
        glEnd();
    }

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(790, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(800, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    renderBitmapString(0, w_height-15, GLUT_BITMAP_HELVETICA_18, "Draw a rectangle window by click 4 times on screen");
    renderBitmapString(0, w_height-35, GLUT_BITMAP_HELVETICA_18, "Right click on screen for open menu bar");
    

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            scale(1.2, 1.2);
            break;
        case 'a':
            scale(0.8, 0.8);
            break;
        case '/':
            rotate(-15);
            break;
        case '\\':
            rotate(+15);
            break;
        case 'x':
            shear(0.3, 0);
            break;
        case 'y':
            shear(0, 0.3);
            break;
        case 'r':
            reflect(-1, -1);
            break;
        case 't':
            reflect(-1, -1);
            break;
        
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            translate(0, 10);
            break;
        case GLUT_KEY_DOWN:
            translate(0, -10);
            break;
        case GLUT_KEY_LEFT:
            translate(-10, 0);
            break;
        case GLUT_KEY_RIGHT:
            translate(10, 0);
            break;
    }
    glutPostRedisplay();
}

void menu(int option){

    if (option == 1){
        reset();
        }

    glutPostRedisplay();
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
            glutPostRedisplay();
        }

        if(count >= 4){
            box[0][0] = x_min;
            box[0][1] = y_min;
            box[0][2] = 1;
            box[1][0] = x_max;
            box[1][1] = y_min;
            box[1][2] = 1;
            box[2][0] = x_max;
            box[2][1] = y_max;
            box[2][2] = 1;
            box[3][0] = x_min;
            box[3][1] = y_max;
            box[3][2] = 1;

            center_x = (x_min + x_max) / 2.0;
            center_y = (y_min + y_max) / 2.0;

            glutPostRedisplay();
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, w_width, 0.0, w_height);
    initialize_matrix();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w_width, w_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    glutCreateMenu(menu);
    glutAddMenuEntry("Translate (arrow keys)", 0);
    glutAddMenuEntry("Scale up (s)", 0);
    glutAddMenuEntry("Scale down (a)", 0);
    glutAddMenuEntry("Rotate Clockwise (/)", 0);
    glutAddMenuEntry("Rotate Anticlockwise (\\)", 0);
    glutAddMenuEntry("Shear X-axis (x)", 0);
    glutAddMenuEntry("Shear Y-axis (y)", 0);
    glutAddMenuEntry("Reflect X-axis (r)", 0);
    glutAddMenuEntry("Reflect Y-axis (t)", 0);
    glutAddMenuEntry("Reset", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
