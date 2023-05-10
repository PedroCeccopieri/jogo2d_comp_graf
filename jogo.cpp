
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "Character.h"
#include "Background.h"
#include "Coin.h"
#include "utils.h"

int width = 500;
int height = 500;
float aspect = width / height;

int frame = 0;

float x_min = -10, y_min = -10, z_min = -10;
float x_max = 10, y_max = 10, z_max = 10;

float xcamera = 0, ycamera = 0, zcamera = 20;


Character character(-4,-3,10);
Background background(12, 12);
Coin coin(0,0,9);

void refresh();

void display() {
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();

	// frame update

	// aspect

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	character.draw();
	character.showHitbox();
	background.draw();
	coin.draw();
	coin.showHitbox();
	
	// refresh();
	// gluLookAt(20*cos(frame/100.0),ycamera,20*sin(frame/100.0),0,0,0,0,1,0);

	glutSwapBuffers();
}

void refresh() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1,2.0,50.0);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	width = w;
	height = h;
	aspect = (float) width/height;

	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	refresh();
	gluLookAt(xcamera,ycamera,zcamera,xcamera,0,0,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {

		case 'm':			
			xcamera++;
			refresh();
			gluLookAt(xcamera,ycamera,zcamera,xcamera,0,0,0,1,0);
			break;
		case 'n':			
			xcamera--;
			refresh();
			gluLookAt(xcamera,ycamera,zcamera,xcamera,0,0,0,1,0);
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

void specialkeys (int key, int x, int y) {
	switch (key) {

		case GLUT_KEY_LEFT:
			character.movePos(-1,0,0);
			break;
		case GLUT_KEY_RIGHT:
			character.movePos(1,0,0);
			break;
		case GLUT_KEY_UP:
			character.movePos(0,1,0);
			break;
		case GLUT_KEY_DOWN:
			character.movePos(0,-1,0);
			break;
	}

}

void init() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void nextFrame(int f) {
	frame++;
	character.animate();
	coin.animate();

	//coin.checkcolision(character.getHitbox());

	// std::cout << coin.checkcolision(character.getHitbox()) << std::endl;
	
	glutPostRedisplay();
    glutTimerFunc(16,nextFrame,0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Jogo");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutTimerFunc(20,nextFrame,0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys);

    init();

    glutMainLoop();
    return 0;
}

