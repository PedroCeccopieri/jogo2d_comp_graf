
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
		case '0':
			character.setState(0);
			break;
		case '1':
			character.setState(1);
			break;
		case '2':
			character.setState(2);
			break;
		case '3':
			character.setState(3);
			break;
		case '4':
			character.setState(4);
			break;
		case '5':
			character.setState(5);
			break;
		case '6':
			character.setState(6);
			break;
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
    glutTimerFunc(16,nextFrame,0);
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

