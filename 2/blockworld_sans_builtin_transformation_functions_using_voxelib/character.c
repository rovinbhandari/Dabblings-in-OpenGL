#include <character.h>
#include <blockworld_complex_figures.h>
#include <blockworld_voxel.h>
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
                        && (y >= b && y <= SIZELEGh + b)\
                        && (z >= c && z <= SIZELEGb + c))
#define LEG1_TEST LEG_TEST(0, 0, 0)
#define LEG2_TEST LEG_TEST(0, 0, SIZEBODYb - SIZELEGb)
#define LEG3_TEST LEG_TEST(SIZEBODYl - SIZELEGl, 0, 0)
#define LEG4_TEST LEG_TEST(SIZEBODYl - SIZELEGl, 0, SIZEBODYb - SIZELEGb)

   else if ( LEG1_TEST || LEG2_TEST || LEG3_TEST || LEG4_TEST )
   {
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
#define HEAD_X_SHIFT SIZEBODYl - 0.8
#define HEAD_Y_SHIFT SIZELEGh + SIZEBODYh - 0.8
#define HEAD_Z_SHIFT 0
#define HEAD1_TEST(a,b,c) (   (x >= a && x <= a + SIZEHEADl1)\
                           && (y >= b && y <= b + SIZEHEADh1)\
                           && (z >= c && z <= c + SIZEHEADb1))

#define HEAD2_TEST(a,b,c) (   (x >= a && x <= a + SIZEHEADl2)\
                           && (y >= b + SIZEHEADh1 && y <=b + SIZEHEADh1 + SIZEHEADh2)\
                           && (z >= c && z <= c + SIZEHEADb2) )
#define HEAD_TEST   HEAD1_TEST(HEAD_X_SHIFT, HEAD_Y_SHIFT, HEAD_Z_SHIFT)\
                  ||HEAD2_TEST(HEAD_X_SHIFT, HEAD_Y_SHIFT, HEAD_Z_SHIFT)
   /* Check for head */
   else if (HEAD_TEST)
   {
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
      vlPutVoxelAt (x, y, z, length);
   }
#define NOSE_X_TEST(a)  ( (x >= a +SIZEHEADl1 - 4 * SIZENOSE / 5)\
                     &&   (x <= a + SIZEHEADl1 - 4 * SIZENOSE / 5 + SIZENOSE))
#define NOSE_Y_TEST(b)  ( (y >= b + SIZEHEADh1 - 4 * SIZENOSE / 5)\
                     &&   (y <= b + SIZEHEADh1 - 4 * SIZENOSE / 5 + SIZENOSE))
#define NOSE_Z_TEST(c)  ( (z >= c + (SIZEHEADb1 - SIZENOSE) / 2)\
                     &&   (z <= c + (SIZEHEADb1 - SIZENOSE) / 2 + SIZENOSE))
#define NOSE_TEST (NOSE_X_TEST(HEAD_X_SHIFT) && NOSE_Y_TEST(HEAD_Y_SHIFT) && NOSE_Z_TEST(HEAD_Z_SHIFT))                     

   /* Check for nose */
   else if (NOSE_TEST)
   {
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture2);
      vlPutVoxelAt (x, y, z, length);
   }
#define EYE_TEST(a,b,c)  (  (x >= a && x <= a + SIZEEYE)\
                         && (y >= b && y <= b + SIZEEYE)\
                         && (z >= c && z <= c + SIZEEYE))
#define EYE1_TEST EYE_TEST(HEAD_X_SHIFT + SIZEHEADl2 - 4 * SIZEEYE / 5,HEAD_Y_SHIFT + SIZEHEADh1 + (SIZEHEADh2 - SIZEEYE) / 2, HEAD_Z_SHIFT + (SIZEHEADb2 - 2 * SIZEEYE) / 4)
#define EYE2_TEST EYE_TEST (HEAD_X_SHIFT + SIZEHEADl2 - 4 * SIZEEYE / 5, HEAD_Y_SHIFT + SIZEHEADh1 + (SIZEHEADh2 - SIZEEYE) / 2, HEAD_Z_SHIFT + 3 * (SIZEHEADb2 - 2 * SIZEEYE) / 4 + SIZEEYE)                       
                           
   /* Check for eyes */
   else if (EYE1_TEST || EYE2_TEST)
   {
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture2);
      vlPutVoxelAt (x, y, z, length);
   }

#define EAR_CHECK_BASE(a,b,c)  (  (x >= a && x <= a + SIZEEARl)\
                               && (y >= b && y <= b + SIZEEARh)\
                               && (z >= c && z <= c + SIZEEARb))
#define EAR1_CHECK(a,b,c) EAR_CHECK_BASE (0, SIZEHEADh1 + SIZEHEADh2, 0)
#define EAR2_CHECK(a,b,c) EAR_CHECK_BASE (0, SIZEHEADh1 + SIZEHEADh2, SIZEHEADb2 - SIZEEARb)

#define EAR_CHECK   ((EAR1_CHECK(HEAD_X_SHIFT,HEAD_Y_SHIFT, HEAD_Z_SHIFT)))
//                  && (EAR2_CHECK(HEAD_X_SHIFT, HEAD_Y_SHIFT, HEAD_Z_SHIFT))))

   /* Check for ears */
   if ( EAR_CHECK )
   {
      printf ("Creating ear\n");
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture1);
      vlPutVoxelAt (x, y, z, length);
   }

/*   // create the two ears
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
*/

}

void bwDog()
{
   voxel_size = 0.1;
   bwDog_ (0, 0, 0, max (max (SIZEBODYl + SIZEHEADl1 + SIZENOSE, SIZEBODYb), SIZEBODYh + SIZELEGh + SIZEEARh + SIZEHEADh2));
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

