#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Vertices of the octagon (8 sides, center at origin)
    GLfloat angleStep = 2.0 * PI / 8;
    GLfloat vertices[8][2];
    for (int i = 0; i < 8; i++) {
        vertices[i][0] = cos(i * angleStep); // X coordinate
        vertices[i][1] = sin(i * angleStep); // Y coordinate
    }

    // Colors for the triangles (8 different colors)
    GLfloat colors[8][3] = {
        {1.0, 0.0, 0.0}, // Red
        {0.0, 1.0, 0.0}, // Green
        {0.0, 0.0, 1.0}, // Blue
        {1.0, 1.0, 0.0}, // Yellow
        {1.0, 0.0, 1.0}, // Magenta
        {0.0, 1.0, 1.0}, // Cyan
        {1.0, 0.5, 0.0}, // Orange
        {0.5, 0.0, 0.5}  // Purple
    };

    // Draw triangles for the octagon
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; i++) {
        // Set color for each triangle
        glColor3fv(colors[i]);

        // Draw the triangle
        glVertex2f(0.0f, 0.0f);                     // Center of the octagon
        glVertex2f(vertices[i][0], vertices[i][1]); // Current vertex
        glVertex2f(vertices[(i + 1) % 8][0],
                   vertices[(i + 1) % 8][1]); // Next vertex
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Octagon with GL_TRIANGLES");

    // Set up the 2D orthographic projection
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white

    // Register display callback function
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
