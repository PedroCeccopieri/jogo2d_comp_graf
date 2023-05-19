#include <GL/glut.h>

#include "utils.h"
#include "Entity.h"

class Coin: public Entity {
    private:
    
        int coinType;

    public:

        Coin(float x, float y, float z, int ct): Entity(x,y,z) {
            
            coinType = ct;
            scale = 0.5;
            wHitbox = 1.25, hHitbox = 1.25, dHitbox = 1.25;
        }

        int getPoint() {
            return coinType;
        }

        void animate() {

            axisx++; axisz++;

            updateHitbox();
        }

        void draw() {

            glPushMatrix();

            glTranslatef(posx,posy,posz);
            glScalef(scale,scale,scale);

            glRotatef(axisx,1,0,0); // rotação corpo x
            glRotatef(axisy,0,1,0); // rotação corpo y
            glRotatef(axisz,0,0,1); // rotação corpo z

            glScalef(wHitbox,hHitbox,dHitbox);

            if (coinType == 1) color(255,255,0);
            else if (coinType == 3) color(0,0,255);
            else if (coinType == 5) color(255,125,0);
            else if (coinType == 10) color(255,0,0);
            drawCube(true);

            glPopMatrix();
        }
};
