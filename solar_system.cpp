#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159f;

float cameraAngleX = 20.0f, cameraAngleY = 30.0f;
int lastMouseX, lastMouseY;
bool isDragging = false;
float zoom = 10.0f; 

struct Planet {
    float distance, radius, speed, angle;
    float r, g, b;
};
// planets
Planet sun     = { 0.0f, 0.3f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f }; // Yellow
Planet mercury = { 1.0f, 0.05f, 1.5f, 0.0f, 0.7f, 0.7f, 0.7f }; // Gray
Planet venus   = { 1.4f, 0.09f, 1.2f, 0.0f, 1.0f, 0.8f, 0.5f }; // Yellowish-orange
Planet earth   = { 1.8f, 0.1f, 1.0f, 0.0f, 0.2f, 0.6f, 1.0f }; // Blue
Planet mars    = { 2.3f, 0.07f, 0.7f, 0.0f, 1.0f, 0.4f, 0.2f }; // Reddish
Planet jupiter = { 3.5f, 0.2f, 0.4f, 0.0f, 1.0f, 0.8f, 0.6f }; // Light brown
Planet saturn  = { 4.5f, 0.18f, 0.3f, 0.0f, 0.9f, 0.8f, 0.5f }; // Pale yellow
Planet uranus  = { 5.5f, 0.12f, 0.2f, 0.0f, 0.5f, 0.8f, 0.8f }; // Cyan
Planet neptune = { 6.5f, 0.12f, 0.15f, 0.0f, 0.2f, 0.4f, 0.8f }; // Deep blue
Planet moon    = { 0.2f, 0.03f, 3.0f, 0.0f, 0.9f, 0.9f, 0.9f }; // Gray

void drawSphere(float radius) {
    glutSolidSphere(radius, 30, 30);
}

void drawOrbit(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float angle = 2 * PI * i / 100;
        glVertex3f(cos(angle) * radius, 0, sin(angle) * radius);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Cam positioning
    glTranslatef(0.0f, 0.0f, -zoom);
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    //sun
    glColor3f(sun.r, sun.g, sun.b);
    drawSphere(sun.radius);

    
    Planet planets[] = {mercury, venus, earth, mars, jupiter, saturn, uranus, neptune};

    for (int i = 0; i < 8; ++i) {
        Planet& p = planets[i];

        glColor3f(0.4f, 0.4f, 0.4f);
        drawOrbit(p.distance);

        float x = cos(p.angle) * p.distance;
        float z = sin(p.angle) * p.distance;

        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        glColor3f(p.r, p.g, p.b);
        drawSphere(p.radius);

        if (i == 2) {
            float mx = cos(moon.angle) * moon.distance;
            float mz = sin(moon.angle) * moon.distance;
            glPushMatrix();
            glTranslatef(mx, 0.0f, mz);
            glColor3f(moon.r, moon.g, moon.b);
            drawSphere(moon.radius);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glutSwapBuffers();
}

void update(int) {
    mercury.angle += mercury.speed * 0.01f;
    venus.angle   += venus.speed * 0.01f;
    earth.angle   += earth.speed * 0.01f;
    mars.angle    += mars.speed * 0.01f;
    jupiter.angle += jupiter.speed * 0.01f;
    saturn.angle  += saturn.speed * 0.01f;
    uranus.angle  += uranus.speed * 0.01f;
    neptune.angle += neptune.speed * 0.01f;
    moon.angle    += moon.speed * 0.02f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    float ratio = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        cameraAngleY += (x - lastMouseX);
        cameraAngleX += (y - lastMouseY);
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        isDragging = (state == GLUT_DOWN);
        lastMouseX = x;
        lastMouseY = y;
    } else if (button == 3) zoom -= 0.3f; 
    else if (button == 4) zoom += 0.3f;   
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Solar System");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}