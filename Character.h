#include <GL/glut.h>
#include <math.h>

#include "utils.h"

class Character {
    private:

        float posx, posy, posz;
        
        float scale = 0.25;

        int animation = 0, da = 5;

        int state = 0;

        float jump = 0;
        
        float axisx = 0, axisy = 90, axisz = 0;

        float wHitbox = 4.5, hHitbox = 14.4, dHitbox = 6;
        double hitbox[24] = {0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0};

        float neckx = 0, necky = 0, neckz = 0;
        float headx = 0, heady = 0, headz = 0;

        float rarmx = 0, rarmy = 0, rarmz = 0;
        float larmx = 0, larmy = 0, larmz = 0;

        float rforearmx = 0, rforearmy = 0, rforearmz = 0;
        float lforearmx = 0, lforearmy = 0, lforearmz = 0;

        float legsx = 0, legsy = 0, legsz = 0;
        float kneesx = 0, kneesy = 0, kneesz = 0;

    public:

        Character(float x, float y, float z) {
            posx = x;
            posy = y;
            posz = z;
        }

        int getState() {
            return state;
        }

        double* getHitbox() {
            return hitbox;
        }

        void movePos(int dx, int dy, int dz) {
            posx += dx;
            posy += dy;
            posz += dz;
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

        void setState(int s) {
            reset();
            state = s;
        }
        
        void reset() {
            animation = 0, da = 5;

            jump = 0;

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

            if (animation == 50) da = -5;
	        if (animation == -50) da = 5;
            animation += da;

            switch (state) {

                case 0: // stopped
                    break;
                case 1: // walking
                    legsx += da;
                    rarmx += da;
                    larmx += da;
                    rforearmx = 15;
                    lforearmx = 15;
                    kneesx = 15;
                    jump += (da % 2) * 0.005;
                    break;
                case 2: // running
                    legsx += da * 1.8;
                    rarmx += da * 1.8;
                    larmx += da * 1.8;
                    rforearmx = 45;
                    lforearmx = 45;
                    kneesx = 45;
                    jump += (da % 2) * 0.01;
                    break;
                case 3: // stopped and shotting
                    rarmx = -90;
                    break;
                case 4: // walking and shotting
                    legsx += da;
                    rarmx = -90;
                    larmx += da;
                    lforearmx = 15;
                    kneesx = 15;
                    jump += (da % 2) * 0.005;
                    break;
                case 5: // running and shotting
                    legsx += da * 1.8;
                    rarmx = -90;
                    larmx += da * 1.8;
                    lforearmx = 45;
                    kneesx = 45;
                    jump += (da % 2) * 0.01;
                    break;
                case 6: // jumping
                    legsx = (animation + 50)/2 * 80.0/50;
                    rarmx = -80 - animation;
                    rforearmx = 45;
                    larmx -= da;
                    lforearmx = 45;
                    kneesx = 45;
                    jump = 2 * (animation + 50)/2 * 3.0/50;
                    break;
            }

            updateHitbox();
        }

        void showHitbox() {

            glPushMatrix();

            glTranslatef(posx,posy + jump,posz);
            glScalef(scale,scale,scale);

            glRotatef(axisx,1,0,0); // rotação corpo x
            glRotatef(axisy,0,1,0); // rotação corpo y
            glRotatef(axisz,0,0,1); // rotação corpo z

            glScalef(wHitbox,hHitbox,dHitbox);
            color(255,255,255);
            drawCube(false);

            glPopMatrix();

            glPointSize(10);
            glBegin(GL_POINTS);
            for (int i = 0; i < 12; i += 3) glVertex3f(hitbox[i],hitbox[i+1],hitbox[i+2]);
            glEnd();
        }

        void updateHitbox() {
            int i, j, k;

            int ord[24] = {-1,-1,1, 1,-1,1, 1,1,1, -1,1,1, -1,-1,-1, 1,-1,-1, 1,1,-1, -1,1,-1};

            for (int a = 0; a < 24; a += 3) {

                i = ord[a]; j = ord[a+1]; k = ord[a+2];

                hitbox[a] = ((0.5*i * wHitbox*cos(axisz*M_PI/180) - 0.5*j * hHitbox*sin(axisz*M_PI/180))*cos(axisy*M_PI/180) + 0.5*k * dHitbox*sin(axisy*M_PI/180)) * scale + posx;
                hitbox[a+1] = ((0.5*i * wHitbox*sin(axisz*M_PI/180) + 0.5*j * hHitbox*cos(axisz*M_PI/180))*cos(axisx*M_PI/180) - (-(0.5*i * wHitbox*cos(axisz*M_PI/180) - 0.5*j * hHitbox*sin(axisz*M_PI/180))*sin(axisy*M_PI/180) + 0.5*k * dHitbox*cos(axisy*M_PI/180))*sin(axisx*M_PI/180)) * scale + posy + jump;
                hitbox[a+2] = ((0.5*i * wHitbox*sin(axisz*M_PI/180) + 0.5*j * hHitbox*cos(axisz*M_PI/180))*sin(axisx*M_PI/180) + (-(0.5*i * wHitbox*cos(axisz*M_PI/180) - 0.5*j * hHitbox*sin(axisz*M_PI/180))*sin(axisy*M_PI/180) + 0.5*k * dHitbox*cos(axisy*M_PI/180))*cos(axisx*M_PI/180)) * scale + posz;
            }
        }

        void draw() {

            glPushMatrix(); // personagem {
            
            glTranslatef(posx,posy + jump,posz);
            glScalef(scale,scale,scale);
            
            glRotatef(axisx,1,0,0); // rotação corpo x
            glRotatef(axisy,0,1,0); // rotação corpo y
            glRotatef(axisz,0,0,1); // rotação corpo z

            glPushMatrix(); // corpo {
            color(0,100,140);
            glScalef(2,4,2);
            drawCube(true);
            glPopMatrix(); // }

            glPushMatrix(); // {

            glTranslatef(0,2,0);
            glRotatef(neckx,1,0,0); // rotação pescoço x 
            glRotatef(necky,0,1,0); // rotação pescoço y
            glRotatef(neckz,0,0,1); // rotação pescoço z

            glPushMatrix(); // pescoço {
            color(255,190,150);
            glTranslatef(0,0.5,0);
            glScalef(1,1,1);
            drawCube(true);
            glPopMatrix(); // }

            glPushMatrix(); // cabeça {
            color(255,190,150);
            glTranslatef(0,1,0);
            glRotatef(headx,1,0,0);
            glRotatef(heady,0,1,0);
            glRotatef(headz,0,0,1);
            glTranslatef(0,2,0);
            glScalef(4,4,4);
            drawCube(true);
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
            drawCube(true);
            glPopMatrix(); // }

            glPushMatrix(); // anti-braço direito {
            //color(255,190,150);
            color(0,0,255);
            glTranslatef(0.5,-2,0);
            glRotatef(-rforearmx,1,0,0);
            glRotatef(-rforearmy,0,1,0);
            glRotatef(-rforearmz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube(true);
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
            drawCube(true);
            glPopMatrix(); // }

            glPushMatrix(); // anti-braço esquerdo {
            color(255,190,150);
            glTranslatef(-0.5,-2,0);
            glRotatef(-lforearmx,1,0,0);
            glRotatef(-lforearmy,0,1,0);
            glRotatef(-lforearmz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube(true);
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPushMatrix(); // {
            
            glTranslatef(0.5,-2,0);
            glRotatef(-legsx,1,0,0); // rotação perna direita x
            glRotatef(-legsy,0,1,0); // rotação perna direita y
            glRotatef(-legsz,0,0,1); // rotação perna direita z
            
            glPushMatrix(); // perna direita {
            color(255,0,0);
            glTranslatef(0,-1.25,0);
            glScalef(1,2.5,2);
            drawCube(true);
            glPopMatrix(); // }

            glPushMatrix(); // joelho direito {
            color(255,190,150);
            glTranslatef(0,-2.5,0);
            glRotatef(kneesx,1,0,0);
            glRotatef(kneesy,0,1,0);
            glRotatef(kneesz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube(true);
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPushMatrix(); // {
            
            glTranslatef(-0.5,-2,0);
            glRotatef(legsx,1,0,0); // rotação perna esquerda x
            glRotatef(legsy,0,1,0); // rotação perna esquerda y
            glRotatef(legsz,0,0,1); // rotação perna esquerda z
            
            glPushMatrix(); // perna esquerda {
            color(255,0,0);
            glTranslatef(0,-1.25,0);
            glScalef(1,2.5,2);
            drawCube(true);
            glPopMatrix(); // }

            glPushMatrix(); // joelho esquerdo {
            // color(255,190,150);
            color(255,255,0);
            glTranslatef(0,-2.5,0);
            glRotatef(kneesx,1,0,0);
            glRotatef(kneesy,0,1,0);
            glRotatef(kneesz,0,0,1);
            glTranslatef(0,-1,0);
            glScalef(1,2,2);
            drawCube(true);
            glPopMatrix(); // }

            glPopMatrix(); // }

            glPopMatrix(); // }
        }
};
