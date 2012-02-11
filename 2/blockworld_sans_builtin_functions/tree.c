#include <tree.h>

void bwLeaf()
{
   GLfloat textureleaf[] = {LEAFRAND0to0_1, LEAFRAND0_3to0_8, LEAFRAND0to0_1, 1.0f};
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

void bwStub()
{
}

void bwTrunk()
{
}

