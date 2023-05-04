#include <GL/glut.h>
#include "utils.h"

class Character {
    private:

        int animation = 0, da = 5;
        
        int axisx = 0, axisy = 0, axisz = 0;

        int neckx = 0, necky = 0, neckz = 0;
        int headx = 0, heady = 0, headz = 0;

        int rarmx = 0, rarmy = 0, rarmz = 0;
        int larmx = 0, larmy = 0, larmz = 0;

        int rforearmx = 0, rforearmy = 0, rforearmz = 0;
        int lforearmx = 0, lforearmy = 0, lforearmz = 0;

        int legsx = 0, legsy = 0, legsz = 0;
        int kneesx = 0, kneesy = 0, kneesz = 0;

    public:

        Character() {
            
        }

        void moveNeck(int dx, int dy, int dz) {
            neckx += dx;
            necky += dy;
            neckz += dz;
        }

        void moveHead(int dx, int dy, int dz) {
            headx += dx;
            heady += dy;
            headz += dz;
        }

        void moveRightArm(int dx, int dy, int dz) {
            rarmx += dx;
            rarmy += dy;
            rarmz += dz;
        }

        void moveLeftArm(int dx, int dy, int dz) {
            rarmx += dx;
            rarmy += dy;
            rarmz += dz;
        }

        void moveRightForearm(int dx, int dy, int dz) {
            rforearmx += dx;
            rforearmy += dy;
            rforearmz += dz;
        }

        void moveLeftForearm(int dx, int dy, int dz) {
            lforearmx += dx;
            lforearmy += dy;
            lforearmz += dz;
        }

        void moveLegs(int dx, int dy, int dz) {
            legsx += dx;
            legsy += dy;
            legsz += dz;
        }

        void moveKnees(int dx, int dy, int dz) {
            kneesx += dx;
            kneesy += dy;
            kneesz += dz;
        }

        void moveAxis(int dx, int dy, int dz) {
            axisx += dx;
            axisy += dy;
            axisz += dz;
        }

        void reset() {
            animation = 0, da = 5;

            neckx = 0, necky = 0, neckz = 0;
            headx = 0, heady = 0, headz = 0;

            rarmx = 0, rarmy = 0, rarmz = 0;
            larmx = 0, larmy = 0, larmz = 0;

            rforearmx = 0, rforearmy = 0, rforearmz = 0;
            lforearmx = 0, lforearmy = 0, lforearmz = 0;

            legsx = 0, legsy = 0, legsz = 0;
            kneesx = 0, kneesy = 0, kneesz = 0;
        }

        void animate() {

            if (animation == 60) da = -5;
	        if (animation == -60) da = 5;
            animation += da;

            legsx += da;
            rarmx += da;
            larmx += da;
        }

        void draw() {
            glPushMatrix(); // personagem {

            glRotatef(axisz,0,0,1); // rotação corpo x
            glRotatef(axisy,0,1,0); // rotação corpo y
            glRotatef(axisx,1,0,0); // rotação corpo z

            glPushMatrix(); // corpo {
            color(0,100,140);
            glScalef(2,4,2);
            drawCube();
            glPopMatrix(); // }

            glPushMatrix(); // {

            glTranslatef(0,2,0);
            glRotatef(neckx,1,0,0); // rotação pescoço x 
            glRotatef(necky,0,1,0); // rotação pescoço y
            glRotatef(neckz,0,0,1); // rotação pescoço z

            glPushMatrix(); // pescoço {
            // color(255,190,150);
            color(0,0,255);
            glTranslatef(0,0.5,0);
            glScalef(1,1,1);
            drawCube();
            glPopMatrix(); // }

            glPushMatrix(); // cabeça {
            color(255,190,150);
            glTranslatef(0,1,0);
            glRotatef(headx,1,0,0);
            glRotatef(heady,0,1,0);
            glRotatef(headz,0,0,1);
            glTranslatef(0,2,0);
            glScalef(4,4,4);
            drawCube();
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPushMatrix(); // {
            
            glTranslatef(1,2,0);
            glRotatef(rarmx,1,0,0); // rotação braço direito x
            glRotatef(rarmy,0,1,0); // rotação braço direito y
            glRotatef(rarmz,0,0,1); // rotação braço direito z
            
            glPushMatrix(); // braço direito {
            color(0,100,140);
            glTranslatef(0.5,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPushMatrix(); // anti-braço direito {
            //color(255,190,150);
            color(0,255,0);
            glTranslatef(0.5,-2,0);
            glRotatef(-rforearmx,1,0,0);
            glRotatef(-rforearmy,0,1,0);
            glRotatef(-rforearmz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPushMatrix(); // {
            
            glTranslatef(-1,2,0);
            glRotatef(-larmx,1,0,0); // rotação braço esquerdo x
            glRotatef(-larmy,0,1,0); // rotação braço esquerdo y
            glRotatef(-larmz,0,0,1); // rotação braço esquerdo z
            
            glPushMatrix(); // braço esquerdo {
            color(0,100,140);
            glTranslatef(-0.5,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPushMatrix(); // anti-braço esquerdo {
            color(255,190,150);
            glTranslatef(-0.5,-2,0);
            glRotatef(-lforearmx,1,0,0);
            glRotatef(-lforearmy,0,1,0);
            glRotatef(-lforearmz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPushMatrix(); // {
            
            glTranslatef(0.5,-2,0);
            glRotatef(-legsx,1,0,0); // rotação perna direita x
            glRotatef(-legsy,0,1,0); // rotação perna direita y
            glRotatef(-legsz,0,0,1); // rotação perna direita z
            
            glPushMatrix(); // perna direita {
            color(255,0,0);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPushMatrix(); // joelho direito {
            color(255,190,150);
            glTranslatef(0,-2,0);
            glRotatef(kneesx,1,0,0);
            glRotatef(kneesy,0,1,0);
            glRotatef(kneesz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPushMatrix(); // {
            
            glTranslatef(-0.5,-2,0);
            glRotatef(legsx,1,0,0); // rotação perna esquerda x
            glRotatef(legsy,0,1,0); // rotação perna esquerda y
            glRotatef(legsz,0,0,1); // rotação perna esquerda z
            
            glPushMatrix(); // perna esquerda {
            color(255,0,0);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPushMatrix(); // joelho esquerdo {
            // color(255,190,150);
            color(255,255,0);
            glTranslatef(0,-2,0);
            glRotatef(kneesx,1,0,0);
            glRotatef(kneesy,0,1,0);
            glRotatef(kneesz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube();
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPopMatrix(); // }
        }
};
