#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>


float cloudOffset = 0.0f;

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void update(int value) {

    cloudOffset += 0.002f;
    if (cloudOffset > 1.5f) {
        cloudOffset = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init(){
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gluOrtho2D(-1.0,1.0,-1.0,1.0);
}

void drawSun(){
    glColor3f(1.0f,1.0f,0.0f);
    float x = 0.8, y = 0.8, r = 0.1;
    
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x,y);

    for(int i =0;i<=360;i++){
        float theta = 2.0 * 3.1415 * i/360;
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);

        glVertex2f(x+dx, y+dy);
    }
    glEnd();
}

void drawBox(float x, float y, float width, float height){

    glBegin(GL_POLYGON);
    
    glVertex2f(x,y);
    glVertex2f(x+width, y);
    glVertex2f(x+width,y+height);
    glVertex2f(x,y+height);

    glEnd();
}

void drawTriangle(float x, float y, float width, float height){

    glBegin(GL_TRIANGLES);

    glVertex2f(x,y);
    glVertex2f(x+(width/2), y + height);
    glVertex2f(x+width , y);

    glEnd();
}


void drawRiver() {
    glColor3f(0.0f, 0.5f, 1.0f);

    glBegin(GL_POLYGON);

    glVertex2f(-1.0f, -0.3f);
    glVertex2f(-1.0f , -0.6f);
    glVertex2f(1.0f , -0.6f);
    glVertex2f(1.0f , -0.3f);

    glEnd();
}

void drawCloudCircle(float x, float y, float radius) {
    int num_segments = 360;
    glColor3f(0.8f, 0.8f, 0.8f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}


void drawCloud(float x, float y, float radius) {
    
    drawCloudCircle(x, y, radius);

    drawCloudCircle(x - radius * 0.6f, y, radius * 0.8f);

    drawCloudCircle(x + radius * 0.6f, y, radius * 0.8f);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    

    // sky 
    glColor3f(0.53f, 0.81f, 0.92f);
    drawBox(-1.0f,0.0f,2.0f,1.0f);

    // grass ground
    glColor3f(0.0f, 0.8f, 0.0f);
    drawBox(-1.0f,0.0f,2.0f,-1.0f);

    //for hills
    glColor4f(0.4f, 0.3f, 0.1f, 0.95f); 
    
    drawTriangle(-0.5f, 0.0f, 0.85f, 0.8f);
    drawTriangle(0.0f, 0.0f, 0.85f, 0.8f);
    drawTriangle(0.6f, 0.0f, 0.85f, 0.8f);
    
    

    drawSun();

    // for upper shop
    glColor3f(0.5f, 0.5f, 0.5f);
    drawBox(-0.8f, 0.0f, 0.15f, 0.2f);

    // for lower shop
    glColor3f(0.2f, 0.2f, 0.2f);
    drawBox(-0.8f, 0.0f, 0.15f, 0.13f);

    // for house body
    glColor3f(1.0f, 0.98f, 0.8f);
    drawBox(-0.3f, -0.05f, 0.4f, 0.4f);

    // for house door
    glColor3f(0.5f, 0.3f, 0.2f);
    drawBox(-0.05f, -0.05f, 0.1f, 0.2f);

    // for window of hpuse
    glColor3f(0.7f, 0.9f, 1.0f);
    drawBox(-0.2f, 0.15f, 0.1f, 0.1f);

    // for house roof
    glColor3f(0.6f, 0.2f, 0.1f);
    drawTriangle(-0.35f, 0.35f, 0.5f, 0.2f);


    // for chimney at roof
    glColor3f(0.4f, 0.4f, 0.4f);
    drawBox(-0.2f, 0.45f, 0.05f, 0.1f);

    // for garage
    glColor3f(0.5f, 0.5f, 0.5f);
    drawBox(0.1f, -0.05f, 0.3f, 0.3f);

    // for river
    // glPushMatrix();
    drawRiver();
    // glPopMatrix();

    // for cloud
    glPushMatrix();

    glTranslatef(cloudOffset, 0.0f, 0.0f);

    drawCloud(-0.6f + cloudOffset, 0.7f, 0.1f);
    drawCloud(-0.4f + cloudOffset, 0.8f, 0.1f);
    drawCloud(0.3f + cloudOffset, 0.7f, 0.1f);

    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(0.75f, -0.9f, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta ");
    renderBitmapString(0.8f, -0.95f, GLUT_BITMAP_HELVETICA_18, "500106034");



    glFlush();
}


int main(int argc, char** argv){
    int mode = GLUT_RGB | GLUT_SINGLE;

    glutInit(&argc, argv); 

    glutInitDisplayMode(mode);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(920,780);

    glutCreateWindow("Dream Hut - Experiment 1");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(16,update,0);
    glutMainLoop();
    return 0;
}