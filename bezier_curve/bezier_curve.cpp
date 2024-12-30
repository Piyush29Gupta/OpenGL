#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

const int w_width = 750;
const int w_height = 750;

int count = 0;

void renderBitmapString(float x, float y, void *font, const char *string) 
{
    glRasterPos2f(x, y);
    while (*string){
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void bezier_curve(float x1, float y1, float x2, float y2, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8) 
{
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        float x = (1 - t) * (1 - t) * (1 - t) * (1 - t) * x1 + 4 * (1 - t) * (1 - t) * (1 - t) * t * p1 + 6 * (1 - t) * (1 - t) * t * t * p3 + 4 * (1 - t) * t * t * t * p5 + t * t * t * t * x2;

        float y = (1 - t) * (1 - t) * (1 - t) * (1 - t) * y1 + 4 * (1 - t) * (1 - t) * (1 - t) * t * p2 + 6 * (1 - t) * (1 - t) * t * t * p4 + 4 * (1 - t) * t * t * t * p6 + t * t * t * t * y2;

        glVertex2f(x, y);
    }
    glEnd();
}


void bezier_curve_linear(float x1, float y1, float x2, float y2, float p1, float p2) 
{
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for(float i = 0.0; i <= 1.0; i += 0.1) {
        float x = (1 - i) * (1 - i) * x1 + 2 * (1 - i) * i * p1 + i * i * x2;
        float y = (1 - i) * (1 - i) * y1 + 2 * (1 - i) * i * p2 + i * i * y2;
        glVertex2f(x, y);
    }
    glEnd();
}

void bezier_curve_quard(float x1, float y1, float x2, float y2, float p1, float p2, float p3, float p4)
{
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for(float i = 0.0; i <= 1.0; i += 0.1) {
        float x = (1 - i) * (1 - i)* (1 - i) * x1 + 3 * (1 - i)* (1 - i) * i * p1 + 3 * (1-i)*i*i*p3 + i * i* i * x2;
        float y = (1 - i) * (1 - i)* (1 - i) * y1 + 3 * (1 - i)* (1 - i) * i * p2 + 3 * (1-i)*i*i*p4 + i * i* i * y2;
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(16);

    bezier_curve_linear(70,495,617,568,143,558);

    glLineWidth(6);

    bezier_curve_linear(205,535,239,263,244,440);

    bezier_curve_quard(484,558,598,300,486,262,536,242);


    glColor3f(0.0,1.0,0.0);

    //P
    if (count>0) {
    glBegin(GL_LINES);
        glVertex2f(20,83);
        glVertex2f(20,175);
    
    glEnd();
    bezier_curve_quard(20,175,20,134,52,175,52,145);
        
    }
    

    //I
    if (count>1) {
    glBegin(GL_LINES);
        glVertex2f(110,175);
        glVertex2f(110,84);
    
    glEnd();
    bezier_curve_quard(76,180,155,176,95,173,136,179);
    bezier_curve_quard(72,75,149,88,90,86,131,77);
        
    }

    //Y
    if (count>2) {
    glBegin(GL_LINES);
        glVertex2f(217,143);
        glVertex2f(222,72);
    
    glEnd();
    bezier_curve_linear(178,179,217,143,192,160);
    bezier_curve_linear(217,143,241,183,235,164);
        
    }

    //U
    if (count>3) {
    bezier_curve_quard(264,178,327,200,282,50,328,50);
        
    }

    //S
    if (count>4) {
    bezier_curve(414,166,376,80,388,220,370,140,460,50,400,10);
    // bezier_curve_quard(414,166,376,70,388,185,405,50);
    }
    
    //H
    if (count>5) {
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(450,170);
        glVertex2f(456,80);

        glVertex2f(495,168);
        glVertex2f(505,80);

        glVertex2f(453,123);
        glVertex2f(501,125);
    
    glEnd();
        
    }

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(w_width-120, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(w_width-100, 40, GLUT_BITMAP_HELVETICA_18, "500106034");

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if(key == 'p' || key == 'i' || key == 'y' || key == 'u' || key == 's' ||key == 'h' ){
        count++;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w_width, 0.0, w_height);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w_width, w_height);
    glutCreateWindow("Exp 11");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
