#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

int WIDTH = 768;
int HEIGHT = 768;

using namespace std;

float zoom_level = 1.0;
float zoom_center_x = 0.0;
float zoom_center_y = 0.0;
float diamond_rotation_angle = 0.0;
float rotation_speed = 1.0;


void renderBitmapString(float x, float y, void *font, const char *string) 
{
    glRasterPos2f(x, y);

    while (*string){
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void UpdateProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(zoom_center_x - WIDTH / 2 * zoom_level,
            zoom_center_x + WIDTH / 2 * zoom_level,
            zoom_center_y - HEIGHT / 2 * zoom_level,
            zoom_center_y + HEIGHT / 2 * zoom_level,
            -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 0.0, 0.0);
    renderBitmapString(750, 20, GLUT_BITMAP_HELVETICA_18, "Piyush Gupta");
    renderBitmapString(750, 40, GLUT_BITMAP_HELVETICA_18, "500106034");
}

void DrawBox(float x, float y, float size) {
    float half = size / 2.0f;
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - half, y - half);
    glVertex2f(x + half, y - half);
    glVertex2f(x + half, y + half);
    glVertex2f(x - half, y + half);
    glEnd();
}

void DrawDiamond(float x, float y, float size) {
    float half = size / 2.0f;
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(diamond_rotation_angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, -half);
    glVertex2f(half, 0.0f);
    glVertex2f(0.0f, half);
    glVertex2f(-half, 0.0f);
    glEnd();
    glPopMatrix();
}

void DrawFractal(float x, float y, float size, int depth) {

    if (depth <= 0 || size < 0.5f){
        return;
    }

    DrawBox(x, y, size);
    DrawDiamond(x, y, size);
    float newSize = size / 2;
    
    DrawFractal(x - newSize / 2, y - newSize / 2, newSize, depth - 1);
    DrawFractal(x + newSize / 2, y - newSize / 2, newSize, depth - 1);
    DrawFractal(x - newSize / 2, y + newSize / 2, newSize, depth - 1);
    DrawFractal(x + newSize / 2, y + newSize / 2, newSize, depth - 1);
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);
    
    int depth = static_cast<int>(std::log2(1.0f / zoom_level)) + 4;

    if (depth > 10){
        depth = 10;
    }
    DrawFractal(0.0f, 0.0f, WIDTH / 2.0f, depth);
    glutSwapBuffers();
}

void Timer(int value) {
    diamond_rotation_angle += rotation_speed;
    if (diamond_rotation_angle >= 360.0f){
        diamond_rotation_angle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, Timer, 0);
}

void KeyboardZoom(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
            zoom_level *= 0.8f;
            break;
        case 'o':
            zoom_level *= 1.25f;
            break;
        default:
            return;
    }
    UpdateProjection();
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Infinite Zoom Fractal with Rotating Diamonds");
    UpdateProjection();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(KeyboardZoom);
    glutTimerFunc(16, Timer, 0);

    

    glutMainLoop();

    

    return 0;
}
