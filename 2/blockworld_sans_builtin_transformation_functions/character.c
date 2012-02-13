#include <character.h>

static GLfloat texture1[] = {0.84, 0.84, 0.84, 1};
static GLfloat texture2[] = {0.01, 0.01, 0.01, 1};

void bwLeg()
{
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwCuboid(SIZELEGl, SIZELEGb, SIZELEGh);
}

void bwTail()
{
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwCuboid(SIZETAILl, SIZETAILb, SIZETAILh);
   glPopMatrix();
  
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwTranslate(SIZETAILl, SIZETAILh - SIZETAILh / 3, 0);
   bwCuboid(SIZETAILl, SIZETAILb, SIZETAILh / 3);
   glPopMatrix();
}

void bwBody()
{
   // create 4 legs
   glPushMatrix();
   bwLeg();
   glPopMatrix();

   glPushMatrix();
   bwTranslate(0, 0, SIZEBODYb - SIZELEGb);
   bwLeg();
   glPopMatrix();

   glPushMatrix();
   bwTranslate(SIZEBODYl - SIZELEGl, 0, 0);
   bwLeg();
   glPopMatrix();

   glPushMatrix();
   bwTranslate(SIZEBODYl - SIZELEGl, 0, SIZEBODYb - SIZELEGb);
   bwLeg();
   glPopMatrix();

   // create trunk
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwTranslate(0, SIZELEGh, 0);
   bwCuboid(SIZEBODYl, SIZEBODYb, SIZEBODYh);
   glPopMatrix();

   // create tail
   glPushMatrix();
   bwTranslate(0, SIZELEGh + SIZEBODYh, (SIZEBODYb - SIZETAILb) / 2);
   bwTail();
   glPopMatrix();
}

void bwHead()
{
   // create the two main parts of the skull
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwTranslate(0, 0, 0);
   bwCuboid(SIZEHEADl1, SIZEHEADb1, SIZEHEADh1);
   glPopMatrix();

   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwTranslate(0, SIZEHEADh1, 0);
   bwCuboid(SIZEHEADl2, SIZEHEADb2, SIZEHEADh2);
   glPopMatrix();

   // create the two ears
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwTranslate(0, SIZEHEADh1 + SIZEHEADh2, 0);
   bwCuboid(SIZEEARl, SIZEEARb, SIZEEARh);
   glPopMatrix();

   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
   bwTranslate(0, SIZEHEADh1 + SIZEHEADh2, SIZEHEADb2 - SIZEEARb);
   bwCuboid(SIZEEARl, SIZEEARb, SIZEEARh);
   glPopMatrix();

   // create two eyes
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture2);
   bwTranslate(SIZEHEADl2 - 4 * SIZEEYE / 5, SIZEHEADh1 + (SIZEHEADh2 - SIZEEYE) / 2, (SIZEHEADb2 - 2 * SIZEEYE) / 4);
   bwCube(SIZEEYE);
   glPopMatrix();

   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture2);
   bwTranslate(SIZEHEADl2 - 4 * SIZEEYE / 5, SIZEHEADh1 + (SIZEHEADh2 - SIZEEYE) / 2, 3 * (SIZEHEADb2 - 2 * SIZEEYE) / 4 + SIZEEYE);
   bwCube(SIZEEYE);
   glPopMatrix();

   // create nose
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture2);
   bwTranslate(SIZEHEADl1 - 4 * SIZENOSE / 5, SIZEHEADh1 - 4 * SIZENOSE / 5, (SIZEHEADb1 - SIZENOSE) / 2);
   bwCube(SIZENOSE);
   glPopMatrix();
}

void bwDog()
{
   glPushMatrix();
   bwBody();
   glPopMatrix();

   glPushMatrix();
   bwTranslate(SIZEBODYl - 0.8, SIZELEGh + SIZEBODYh - 0.8, 0);
   bwHead();
   glPopMatrix();
}

