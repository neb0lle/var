#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

float angle = 0;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
float tX = 0;
float tY = 0;
float tZ = 0;
double valZoom = 10.0;
double camX = 0, camY = 0, camZ = 10.0;

// Callback: Mouse click event
void sphereMouseEvent(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = (yrot + x);
        ydiff = -y + xrot;
    } else {
        mouseDown = false;
    }
}

// Callback: Mouse motion event for sphere rotation
void sphereMouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = -(x + xdiff);
        xrot = (y + ydiff);

        if (xrot > 89.0f)
            xrot = 89.0f;
        if (xrot < -89.0f)
            xrot = -89.0f;

        camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
        camY = valZoom * (sin(xrot * PI / 180));
        camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
    }
    glutPostRedisplay();
}

// Set material properties for lighting
void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
                 GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
                 GLfloat specularR, GLfloat specularG, GLfloat specularB,
                 GLfloat shininess) {
    GLfloat ambient[] = {ambientR, ambientG, ambientB};
    GLfloat diffuse[] = {diffuseR, diffuseG, diffuseB};
    GLfloat specular[] = {specularR, specularG, specularB};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(tX, tY, tZ);

    glutWireSphere(1, 50, 50);
    glFlush();
}

// Reshape callback function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}

// Initialize lighting
void initLight() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat lightpos[] = {0.0, 0.0, 15.0};
    GLfloat lightcolor[] = {0.5, 0.5, 0.5};
    GLfloat ambcolor[] = {0.2, 0.2, 0.2};
    GLfloat specular[] = {1.0, 1.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambcolor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_COLOR_MATERIAL);
}

// Idle function for animation
void animate() {
    angle += 0.1;
    glutPostRedisplay();
}

// Keyboard input callback
void keyBoard(unsigned char key, int x, int y) {
    switch (key) {
        case 'A':
        case 'a':
            tX -= 0.1;
            break;
        case 'D':
        case 'd':
            tX += 0.1;
            break;
        case 'W':
        case 'w':
            tY += 0.1;
            break;
        case 'S':
        case 's':
            tY -= 0.1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Special key (arrow keys) input callback
void arrowKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            valZoom += 0.1;
            break;
        case GLUT_KEY_DOWN:
            valZoom -= 0.1;
            break;
        default:
            break;
    }

    camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
    camY = valZoom * (sin(xrot * PI / 180));
    camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("my first openGL");
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    initLight();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.0001, 100);

    glutIdleFunc(animate);
    glutMouseFunc(sphereMouseEvent);
    glutMotionFunc(sphereMouseMotion);
    glutKeyboardFunc(keyBoard);
    glutSpecialFunc(arrowKey);

    glutMainLoop();
}
