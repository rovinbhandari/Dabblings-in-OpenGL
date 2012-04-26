#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include <stdio.h>
#include <general.h>

typedef struct _MatrixStack 
{
  float topMatrix[16];
  struct _MatrixStack *prev;
}MatrixStack;


enum 
{
  MODELVIEW,
  PROJECTION
};

void setMatrixMode(int a);
int getMatrixMode();
MatrixStack *initMatrix();
MatrixStack *pushMatrix();
MatrixStack *popMatrix();
MatrixStack *multMatrix(float *matrixB);
MatrixStack *translate(float x,float y,float z);
MatrixStack *scale(float x,float y,float z);
MatrixStack *rotate(float degree,int x, int y,int z);
Vertex globalVertex(Vertex a);
Vertex eyeVertex(Vertex a);

#endif // end of file
