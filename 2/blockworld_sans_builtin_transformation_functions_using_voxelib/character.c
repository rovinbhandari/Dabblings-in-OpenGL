#include <character.h>
#include <blockworld_complex_figures.h>
#include <voxel.h>
#include <common.h>

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

double voxel_size;

void bwDog_ (double x, double y, double z, double length)
{
   VOXEL_LEN_TEST (x, y, z, length, voxel_size, bwDog_);

   /* Check of bod trunk*/
   if (   ( x >= 0 && x <= SIZEBODYl )
       && ( y >= SIZELEGh && y <= SIZELEGh + SIZEBODYh)
       && ( z >= 0 && z <= SIZEBODYb))
   {
      // create trunk
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
      vlPutVoxelAt(x, y, z, length);
   }
   /* Check for legs */
#define LEG_TEST(a,b,c) (  (x >= a && x <= SIZELEGl + a)\
                        && (y >= c && y <= SIZELEGh + c)\
                        && (z >= b && z <= SIZELEGb + b))
#define LEG1_TEST LEG_TEST(0, 0, 0)
#define LEG2_TEST LEG_TEST(0, 0, SIZEBODYb - SIZELEGb)
#define LEG3_TEST LEG_TEST(SIZEBODYl - SIZELEGl, 0, 0)
#define LEG4_TEST LEG_TEST(SIZEBODYl - SIZELEGl, 0, SIZEBODYb - SIZELEGb)

   else if ( LEG1_TEST || LEG2_TEST || LEG3_TEST || LEG4_TEST )
   {
      // TODO : TEXTURE ??
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
      vlPutVoxelAt (x, y, z, length);
   }   
#define TAIL_ROOT_TEST(a,b,c) ( (x >= a && x <= a + SIZETAILl)\
                             && (y >= b && y <= b + SIZETAILh)\
                             && (z >= c && z <= c + SIZETAILb))
#define TAIL_TOP_TEST(a,b,c)  (  (x >= a + SIZETAILl && x <= a + SIZETAILl + SIZETAILl)\
                       && (y >= b + SIZETAILh - SIZETAILh/3 && y <= b + SIZETAILh/3)\
                       && (z >= c && z <= c + SIZETAILb) )
#define FINAL_ROOT_TEST TAIL_ROOT_TEST(0,SIZELEGh+SIZEBODYh,(SIZEBODYb-SIZETAILb)/2)
#define FINAL_TOP_TEST TAIL_TOP_TEST(0,SIZELEGh+SIZEBODYh,(SIZEBODYb-SIZETAILb)/2)
   /* Check for tail */
   else if ( FINAL_TOP_TEST || FINAL_ROOT_TEST )
   {
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
      vlPutVoxelAt (x, y, z, length);
   }
}

void bwDog()
{
   voxel_size = 0.5;
//   bwDog_ (0, 0, 0, max (max (SIZEBODYl + SIZEHEADl + SIZENOSE, SIZEBODYb + SIZEHEADb), SIZEBODYh + SIZELEGh + SIZEEARh))
/*
   glPushMatrix();
   bwBody();
   glPopMatrix();

   glPushMatrix();
   bwTranslate(SIZEBODYl - 0.8, SIZELEGh + SIZEBODYh - 0.8, 0);
   bwHead();
   glPopMatrix();
*/   
}

