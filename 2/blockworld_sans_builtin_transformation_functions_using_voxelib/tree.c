#include <tree.h>
#include <blockworld_complex_figures.h>
#include <common.h>

#define COLRANDRB        ((rand() % 101) / 1000.0f)     // Yo!   // [0, 0.1]
#define COLRANDG         ((rand() % 31) / 100.0f + 0.2f)         // [0.2, 0.5]
void bwBranch_(GLdouble x, GLdouble y ,GLdouble z, GLdouble length)
{
  VOXEL_LEN_TEST (x, y, z, length, SIZELEAF, bwBranch_);

  if (   ( x >= 0) && (x <= SIZEBRANCH)
      && ( y >= 0) && (y <= SIZEBRANCH)
      && ( z >= 0) && (z <= SIZEBRANCH))
  {
    if((rand() % 1000) < 100)
    {
        GLfloat textureleaf[] = {COLRANDRB, COLRANDG, COLRANDRB, 1.0f};
        glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureleaf);
    	vlPutVoxelAt (x, y, z, length);
    }
    
  }
}

void bwBranch()
{
   vlInit(SIZELEAF);
   bwBranch_(0, 0, 0, SIZEBRANCH);
}

void bwMainBranch()
{
   glPushMatrix();
   bwBranch();
   glPopMatrix();
   glPushMatrix();
   bwTranslate(0, 0, SIZEBRANCH);
   bwBranch();
   glPopMatrix();
   glPushMatrix();
   bwTranslate(0, SIZEBRANCH, 0);
   bwBranch();
   glPopMatrix();
   glPushMatrix();
   bwTranslate(0, SIZEBRANCH, SIZEBRANCH);
   bwBranch();
   glPopMatrix();
   
   glPushMatrix();
   bwTranslate(SIZEBRANCH, SIZEBRANCH / 2, 0);
   bwBranch();
   glPopMatrix();
   glPushMatrix();
   bwTranslate(SIZEBRANCH, SIZEBRANCH / 2, SIZEBRANCH);
   bwBranch();
   glPopMatrix();
   glPushMatrix();
   bwTranslate(SIZEBRANCH, -1 * SIZEBRANCH / 2, SIZEBRANCH / 3);
   bwBranch();
   glPopMatrix();
   
   glPushMatrix();
   bwTranslate(2.1 * SIZEBRANCH, SIZEBRANCH / 2, SIZEBRANCH / 2);
   bwBranch();
   glPopMatrix();
}


#define COLOURNORMALIZER   (0.7d / 255)
#define C   COLOURNORMALIZER
#define SIZETRUNK          (SIZESTUB * NSTUBSINTRUNK)
void bwTrunk_(GLdouble x, GLdouble y ,GLdouble z, GLdouble length)
{
  VOXEL_LEN_TEST (x, y, z, length, SIZESTUB / 36, bwTrunk_);

  if (   ( x >= 0) && (x <= SIZESTUB)
      && ( y >= 0) && (y <= SIZETRUNK)
      && ( z >= 0) && (z <= SIZESTUB))
  {
  GLfloat texturebark2[] = {C * 82, C * 41, 0, 1.0f};
  
        glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texturebark2);
    	vlPutVoxelAt (x, y, z, length);
   
  }
}	

void bwTrunk()
{
   vlInit(SIZESTUB / 36);
   bwTrunk_(0, 0, 0, SIZETRUNK);
}



#define SIZEMAINBRANCHl    (SIZEBRANCH * 3)
#define SIZEMAINBRANCHh    (SIZEBRANCH * 2)
void bwTree()
{
  
   glPushMatrix();
   bwTrunk();
   glPopMatrix();
   
   int i, j;
   for(i = 0; i < MAINBRANCHLEVELS; i++)
      for(j = 0; j < NMAINBRANCHESONLEVEL; j++)
      {
         glPushMatrix();
         bwTranslate(2 * SIZESTUB, SIZETRUNK + (1 + i) * SIZEMAINBRANCHh, 2 * SIZESTUB);
         bwRotate((j * SEPARATIONBWMAINBRANCHES) % 360, 0, 1, 0);
         bwMainBranch();
         glPopMatrix();
         
         glPushMatrix();
         bwTranslate(SIZESTUB + SIZEMAINBRANCHl, SIZETRUNK + (1 + i) * SIZEMAINBRANCHh, 0);
         bwRotate((j * SEPARATIONBWMAINBRANCHES + SEPARATIONBWMAINBRANCHES / 2) % 360, 0, 1, 0);
         bwMainBranch();
         glPopMatrix();
        
       }
   
   for(j = 0; j < NMAINBRANCHESONLEVEL; j++)
   {
      glPushMatrix();
      bwTranslate(0, SIZETRUNK + (1 + i) * SIZEMAINBRANCHh - SIZEBRANCH / 2, 0);
      bwRotate(j * SEPARATIONBWMAINBRANCHES, 0, 1, 0);
      bwMainBranch();
      glPopMatrix();
   }
   
   glPushMatrix();
   bwTranslate(0, SIZETRUNK + (2 + i) * SIZEMAINBRANCHh - SIZEBRANCH / 2, 0);
   bwBranch();
   glPopMatrix();
}

