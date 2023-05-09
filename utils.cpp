#include <GL/glut.h>

#include "utils.h"

void color(int r, int g, int b) {
	glColor3f((float)r/255,(float)g/255,(float)b/255);
}

void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, int stroke) {
	glPushMatrix();
	glLineWidth(stroke);
	glBegin(GL_LINES);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
	glEnd();
	glPopMatrix();
}

void drawSquare() {
	glBegin(GL_QUADS);
		glVertex2f(-1,-1);
		glVertex2f(1,-1);
		glVertex2f(1,1);
		glVertex2f(-1,1);
	glEnd();
}

void drawCube() {
	glutSolidCube(1);
}