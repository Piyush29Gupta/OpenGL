#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

const int w_width = 900;
const int w_height = 750;

float x_1 = 0, y_1 = 0;
float x_2 = 0, y_2 = 0;
float x_3 = 0, y_3 = 0;
float x_4 = 0, y_4 = 0;

float x_point = 0, y_point = 0;

int count = 0;


void display(){

    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    

    if(count == 4){

        glBegin(GL_LINE_LOOP);

        glColor3f(1.0f, 1.0f, 1.0f); 

        // glRectf(x_1,x_2,x_3,x_4);
        
        glVertex2f(x_1,y_1);
        glVertex2f(x_2,y_2);
        glVertex2f(x_3,y_3);
        glVertex2f(x_4,y_4);

        
        
        glEnd();
    }

    if(count==5){


        glBegin(GL_POINTS);

        glColor3f(1.0f,1.0f,1.0f);
        glPointSize(14);
        glLineWidth(14);
        glVertex2f(x_point,y_point);

        glEnd();
        glFlush();

        if(x_point>x_1 && x_point < x_4){
            printf("point is inside \n");
        }
        else{
            printf("Point is outside \n");
        }
    }
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w_width, 0.0, w_height);
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state ==GLUT_DOWN ){
        if(count == 5){
            count = 4;
        }
        if(count == 0){
            count++;
            x_1 = x;
            y_1 = w_height-y;
        }
        else if(count == 1){
            count++;
            x_2 = x;
            y_2 = w_height-y;
        }
        else if(count == 2){
            count++;
            x_3 = x;
            y_3 = w_height-y;
        }
        else if(count == 3){
            count++;
            x_4 = x;
            y_4 = w_height-y;
        }
        else if(count == 4){
            count++;
            x_point = x;
            y_point = w_height-y;
        }
        glutPostRedisplay();
    }
}

int main(int argc , char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 20);
    glutInitWindowSize(w_width, w_height);

    glutCreateWindow("Point clipping");
     init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
   

    glutMainLoop();
    return 0;
    
}