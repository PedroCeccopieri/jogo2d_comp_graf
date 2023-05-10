#include <GL/glut.h>
#include <math.h>
#include <iostream>

#include "utils.h"

class Coin {
    private:
        
        float posx, posy, posz;

        float scale = 1;

        float axisx = 0, axisy = 0, axisz = 0;

        float wHitbox = 1.25, hHitbox = 1.25, dHitbox = 1.25;
        double hitbox[24] = {0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0};

    public:

        Coin(float x, float y, float z) {
            posx = x;
            posy = y;
            posz = z;
        }

        bool checkcolision(double hb[24]) {

            return false;
        }

        void animate() {

            axisy++; axisz++;

            updateHitbox();
        }

        void showHitbox() {

            glPushMatrix();

            glTranslatef(posx,posy,posz);
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
            for (int i = 0; i < 24; i += 3) glVertex3f(hitbox[i],hitbox[i+1],hitbox[i+2]);
            glEnd();
        }

        void updateHitbox() {
            int i, j, k;

            int ord[24] = {-1,-1,1, 1,-1,1, 1,1,1, -1,1,1, -1,-1,-1, 1,-1,-1, 1,1,-1, -1,1,-1};

            for (int a = 0; a < 24; a += 3) {

                i = ord[a]; j = ord[a+1]; k = ord[a+2];

                hitbox[a] = ((0.5*i * wHitbox*cos(axisz*M_PI/180) - 0.5*j * hHitbox*sin(axisz*M_PI/180))*cos(axisy*M_PI/180) + 0.5*k * dHitbox*sin(axisy*M_PI/180)) * scale + posx;
                hitbox[a+1] = ((0.5*i * wHitbox*sin(axisz*M_PI/180) + 0.5*j * hHitbox*cos(axisz*M_PI/180))*cos(axisx*M_PI/180) - (-(0.5*i * wHitbox*cos(axisz*M_PI/180) - 0.5*j * hHitbox*sin(axisz*M_PI/180))*sin(axisy*M_PI/180) + 0.5*k * dHitbox*cos(axisy*M_PI/180))*sin(axisx*M_PI/180)) * scale + posy;
                hitbox[a+2] = ((0.5*i * wHitbox*sin(axisz*M_PI/180) + 0.5*j * hHitbox*cos(axisz*M_PI/180))*sin(axisx*M_PI/180) + (-(0.5*i * wHitbox*cos(axisz*M_PI/180) - 0.5*j * hHitbox*sin(axisz*M_PI/180))*sin(axisy*M_PI/180) + 0.5*k * dHitbox*cos(axisy*M_PI/180))*cos(axisx*M_PI/180)) * scale + posz;
            }
        }

        void draw() {

            glPushMatrix();

            glTranslatef(posx,posy,posz);
            glScalef(scale,scale,scale);

            glRotatef(axisx,1,0,0); // rotação corpo x
            glRotatef(axisy,0,1,0); // rotação corpo y
            glRotatef(axisz,0,0,1); // rotação corpo z

            glScalef(wHitbox,hHitbox,dHitbox);

            color(255,255,0);
            drawCube(true);

            glPopMatrix();
        }

};
