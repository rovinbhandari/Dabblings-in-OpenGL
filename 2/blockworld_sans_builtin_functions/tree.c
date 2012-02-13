#include <tree.h>

#define COLRANDRB        ((rand() % 101) / 1000.0f)     // Yo!   // [0, 0.1]
#define COLRANDG         ((rand() % 31) / 100.0f + 0.2f)         // [0.2, 0.5]
void bwLeaf()
{
   GLfloat textureleaf[] = {COLRANDRB, COLRANDG, COLRANDRB, 1.0f};   // Yo!
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureleaf);
   bwCube(SIZELEAF);
}

void bwBranch()
{
   GLdouble i, j, k;
   for(i = 0.0d; i < SIZEBRANCH; i += SIZELEAF)
      for(j = 0.0d; j < SIZEBRANCH; j += SIZELEAF)
         for(k = 0.0d; k < SIZEBRANCH; k += SIZELEAF)
         {
            if((rand() % 1000) > 100)
               continue;
            glPushMatrix();
            bwTranslate(i, j, k);
            bwLeaf();
            glPopMatrix();
         }
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

#define THICKBARKCHECK(x)   (!(x % 3))
#define THICKNESSOUTERLAYER (3 * SIZEBARK)
#define THICKNESSINNERLAYER (1 * SIZEBARK)
#define A   THICKNESSOUTERLAYER
#define B   THICKNESSINNERLAYER
#define Z   0.0d
#define INNERCOND1   (i >= A && i <= A + B && k >= A && k <= e - A)
#define INNERCOND2   (i >= A && i <= e - A && k >= e - (A + B) && k <= e - A)
#define INNERCOND3   (i >= e - (A + B) && i <= e - A && k >= A && k <= e - A)
#define INNERCOND4   (i >= A && i <= e - A && k >= A && k <= A + B)
#define OUTERCOND1   (i >= Z && i <= A && k >= Z && k <= e)
#define OUTERCOND2   (i >= Z && i <= e && k >= e - A && k <= e)
#define OUTERCOND3   (i >= e - A && i <= e && k >= Z && k <= e)
#define OUTERCOND4   (i >= Z && i <= e && k >= Z && k <= A)
#define OUTERCOND5   (THICKBARKCHECK((GLint) (i / A)) && THICKBARKCHECK((GLint) (k / A)))
#define COLOURNORMALIZER   (0.7d / 255)
#define C   COLOURNORMALIZER
void bwStub()
{
   GLfloat texturebark1[] = {C * 102, C * 52, 0, 1.0f};
   GLfloat texturebark2[] = {C * 82, C * 41, 0, 1.0f};
   GLdouble i, j, k, e = SIZESTUB;
   for(i = 0.0d; i < e; i += SIZEBARK)
      for(j = 0.0d; j < e; j += SIZEBARK)
         for(k = 0.0d; k < e; k += SIZEBARK)
         {
            
            if(INNERCOND1 || INNERCOND2 || INNERCOND3 || INNERCOND4)
            {
               glPushMatrix();
               bwTranslate(i, j, k);
               glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texturebark1);
               bwCube(SIZEBARK);
               glPopMatrix();
            }
            /*
            if(bwCompareDouble(j, 0.0d) || bwCompareDouble(j, e - SIZEBARK))
            {
               glPushMatrix();
               bwTranslate(i, j, k);
               glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texturebark1);
               bwCube(SIZEBARK);
               glPopMatrix();
            }
            */
            if((OUTERCOND1 || OUTERCOND2 || OUTERCOND3 || OUTERCOND4) && OUTERCOND5)
            {
               glPushMatrix();
               bwTranslate(i, j, k);
               glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texturebark2);
               bwCube(SIZEBARK);
               glPopMatrix();
            }
         }
}

void bwTrunk()
{
   int i;
   for(i = 1; i <= NSTUBSINTRUNK; i++)
   {
      glPushMatrix();
      bwTranslate(0, i * SIZESTUB, 0);
      bwStub(SIZESTUB);
      glPopMatrix();
   }
}

#define SIZETRUNK          (SIZESTUB * NSTUBSINTRUNK)
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
      bwTranslate(0, SIZETRUNK + (1 + i) * SIZEMAINBRANCHh, 0);
      bwRotate(j * SEPARATIONBWMAINBRANCHES, 0, 1, 0);
      bwMainBranch();
      glPopMatrix();
   }
   
   glPushMatrix();
   bwTranslate(0, SIZETRUNK + (2 + i) * SIZEMAINBRANCHh, 0);
   bwBranch();
   glPopMatrix();
}

