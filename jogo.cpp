
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "Character.h"
#include "utils.h"

int width = 500;
int height = 500;
float aspect = width / height;

int frame = 0;

float x_min = -10, y_min = -10, z_min = -10;
float x_max = 10, y_max = 10, z_max = 10;

Character character;

void display() {
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();

	// frame update

	// aspect

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	character.draw();

	// print grid
	
	// glColor3f(255,255,255);
	// for (int i = y_min; i < y_max; i++) drawLine(x_max,i,x_min,i,0,1);
	// for (int i = x_min; i < x_max; i++) drawLine(i,y_max,i,y_min,0,1);

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	width = w;
	height = h;
	aspect = (float) width/height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x_min, x_max, y_min, y_max, z_min, z_max);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {

		case 'a':
			character.moveRightForearm(5,0,0);
			character.moveLeftForearm(5,0,0);
			character.moveKnees(5,0,0);
			break;
		case 'A':
			character.moveRightForearm(-5,0,0);
			character.moveLeftForearm(-5,0,0);
			character.moveKnees(-5,0,0);
			break;
		case 's':
			character.moveRightForearm(0,5,0);
			character.moveLeftForearm(0,5,0);
			character.moveKnees(0,5,0);
			break;
		case 'S':
			character.moveRightForearm(0,-5,0);
			character.moveLeftForearm(0,-5,0);
			character.moveKnees(0,-5,0);
			break;
		case 'd':
			character.moveRightForearm(0,0,5);
			character.moveLeftForearm(0,0,5);
			character.moveKnees(0,0,5);
			break;
		case 'D':
			character.moveRightForearm(0,0,-5);
			character.moveLeftForearm(0,0,-5);
			character.moveKnees(0,0,-5);
			break;

		case 'q':
			character.moveNeck(5,0,0);
			break;
		case 'Q':
			character.moveNeck(-5,0,0);
			break;
		case 'w':
			character.moveNeck(0,5,0);
			break;
		case 'W':
			character.moveNeck(0,-5,0);
			break;
		case 'e':
			character.moveNeck(0,0,5);
			break;
		case 'E':
			character.moveNeck(0,0,-5);
			break;

		case 'r':
			character.moveHead(5,0,0);
			break;
		case 'R':
			character.moveHead(-5,0,0);
			break;
		case 't':
			character.moveHead(0,5,0);
			break;
		case 'T':
			character.moveHead(0,-5,0);
			break;
		case 'y':
			character.moveHead(0,0,5);
			break;
		case 'Y':
			character.moveHead(0,0,-5);
			break;


		case 'p':
			character.moveAxis(5,0,0);
			break;
		case 'P':
			character.moveAxis(-5,0,0);
			break;

		case 'o':
			character.moveAxis(0,5,0);
			break;
		case 'O':
			character.moveAxis(0,-5,0);
			break;

		case 'i':
			character.moveAxis(0,0,5);
			break;
		case 'I':
			character.moveAxis(0,0,-5);
			break;

		case ';':
			character.reset();

	}
}

void init() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x_min, x_max, y_min, y_max, z_min, z_max);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void nextFrame(int f) {
	frame++;
	character.animate();
	
	glutPostRedisplay();
    glutTimerFunc(20,nextFrame,0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Jogo");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutTimerFunc(20,nextFrame,0);
	glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();
    return 0;
}

