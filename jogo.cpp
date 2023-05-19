
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "Background.h"

#include "Entity.h"
#include "Character.h"
#include "Coin.h"
#include "utils.h"

int width = 500;
int height = 500;
float aspect = width / height;

int frame = 0;

bool run = false, shooting = false;

float x_min = -10, y_min = -10, z_min = -10;
float x_max = 10, y_max = 10, z_max = 10;

float xcamera = 0, ycamera = 0, zcamera = 30;

bool keystates[256];

Background background(18, 18);
Character character(-10,-8,10);

std::vector<Coin> coins = {Coin(-3,0,9,1), Coin(-1,0,9,3),Coin(1,0,9,5), Coin(3,0,9,10)};

void refresh();

void display() {
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();

	// frame update

	// aspect


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	background.draw();
	character.draw();

	for (int i = 0; i < coins.size(); i++) coins[i].draw();

	character.showHitbox();
	// coin.showHitbox();
	
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
	glutPostRedisplay();
}

void keysAction() {

	if (keystates['m']) {
		xcamera++;
		refresh();
		gluLookAt(xcamera,ycamera,zcamera,xcamera,0,0,0,1,0);
	}
	if (keystates['n']) {
		xcamera--;
		refresh();
		gluLookAt(xcamera,ycamera,zcamera,xcamera,0,0,0,1,0);
	}
		
	if (keystates['p']) character.moveAxis(5,0,0);
	if (keystates['P']) character.moveAxis(-5,0,0);
		

	if (keystates['o']) character.moveAxis(0,5,0);
	if (keystates['O']) character.moveAxis(0,-5,0);

	if (keystates['i']) character.moveAxis(0,0,5);
	if (keystates['I']) character.moveAxis(0,0,-5);

	if (keystates['z']) run = true;
	else run = false;
	if (keystates['x']) shooting = true;
	else shooting = false;

	if (keystates[GLUT_KEY_RIGHT]){
		character.movePos(1,0,0);
		character.resetInterpx();
	}
	if (keystates[GLUT_KEY_LEFT]) {
		character.movePos(-1,0,0);
		character.resetInterpx();
	} 
	if (keystates[GLUT_KEY_UP]) {
		character.movePos(0,1,0);
		character.resetInterpy();
	}
	if (keystates[GLUT_KEY_DOWN]) {
		character.movePos(0,-1,0);
		// character.resetInterpy();
	}
}

void show() {
	// for (int i = 0; i < 256; i++) std::cout << keystates[i] << ' ';
	// std::cout << std::endl;
}

void keyboard (unsigned char key, int x, int y) {
	keystates[key] = true;
	std::cout << "key down: " << key << std::endl;
	show();
}

void specialkeys (int key, int x, int y) {
	keystates[key] = true;
	std::cout << "key down: " << key << std::endl;
	show();
}

void keyboardUp (unsigned char key, int x, int y) {
	keystates[key] = false;
	std::cout << "key up: " << key << std::endl;
	show();
}

void specialkeysUp (int key, int x, int y) {
	keystates[key] = false;
	std::cout << "key up: " << key << std::endl;
	show();
}

void init() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	for (int i = 0; i < 256; i++) keystates[i] = false;
}

void nextFrame(int f) {
	frame++;

	keysAction();

	character.updatePos();
	
	if (character.getInterpx() < INTER) {
		character.nextInterpx();
	}

	if (character.getInterpy() < INTER) {
		character.nextInterpy();
	}

	if (character.getInterpx() < INTER && !run && !shooting) character.setState(1);
	else if (character.getInterpx() < INTER && run && !shooting) character.setState(2);
	else if (character.getInterpx() == INTER && shooting) character.setState(3);
	else if (character.getInterpx() < INTER && !run && shooting) character.setState(4);
	else if (character.getInterpx() < INTER && run && shooting) character.setState(5);
	else character.setState(0);

	// xcamera = character.getPosx();

	// refresh();
	// gluLookAt(xcamera,ycamera,zcamera,xcamera,0,0,0,1,0);

	character.animate();
	for (int i = 0; i < coins.size(); i++) {
		coins[i].animate();
		if (character.checkcolision(coins[i].getHitbox())) {
			std::cout << coins[i].getPoint() << std::endl;
		}
	}
	
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
    glutTimerFunc(16,nextFrame,0);

	glutIgnoreKeyRepeat(1);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys);

	glutKeyboardUpFunc(keyboardUp);
	glutSpecialUpFunc(specialkeysUp);

	//glutSpecialUpFunc();

    init();

    glutMainLoop();
    return 0;
}

