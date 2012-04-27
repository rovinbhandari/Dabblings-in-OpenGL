#include <matrixmanipulation.h>
#include <string.h>

MatrixStack *mStack = NULL;   // Modelview stack
MatrixStack *pStack = NULL;   // Projection view stack
MatrixStack **stack = &mStack;

int matrixMode = MODELVIEW;   // Default mode set to Modelview.

#define SIZEOF_MATRIX sizeof (float) * 16 
#define index(i,j) i * 4 + j

/* 4 x 4 Identity matrix (defined as 1D array) */
float identitymatrix[16] = 
{
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

void setMatrixMode (MatrixMode mode)
{
  matrixMode = mode;
  stack = (matrixMode == MODELVIEW) ? (&mStack) : (&pStack);
}

int getMatrixMode ()
{
  return matrixMode;
}

MatrixStack *initMatrix ()
{
  MatrixStack *temp;

  //Free any previous stack memory
  while(temp = *stack)
  {
    *stack = temp->prev;
    free (temp);
  }
  
  //Add an identity matrix as the top
  *stack = (MatrixStack*) malloc (sizeof (MatrixStack));
  memcpy ((*stack)->topMatrix, identitymatrix, SIZEOF_MATRIX);
  (*stack)->prev = NULL;
  return *stack;
}

MatrixStack *pushMatrix()
{
  MatrixStack *temp;
  temp = (MatrixStack*) malloc (sizeof (MatrixStack));

  // Copy the top of the stack
  memcpy (temp->topMatrix, (*stack)->topMatrix, SIZEOF_MATRIX);

  temp->prev = *stack;
  *stack = temp;
  return *stack;
}

MatrixStack *popMatrix()
{
  MatrixStack *temp;

  if(temp = *stack)
  {
    // If the stack's not empty. Delete the top most element.
    *stack = (*stack)->prev;
    free (temp);
  } 
  else 
  {
    printf ("Matrix not initialized.\n");
  }
  return NULL;
}

MatrixStack *multMatrix (float *matrixB)
{
  int i, j, k;
  float matrixC[16], *matrixA = (*stack)->topMatrix;

  for(i = 0; i < 4; i++)
  {
    for(j = 0; j < 4; j++)
    {
      // Fill the (i,j)th element of the matrix.
      matrixC[i * 4 + j] = 0;                         
      for (k = 0; k < 4; k++)
      {
        matrixC[index (i,j)] += matrixA[index (i,k)] * matrixB[index (k,j)];
      }

    }
  }
  
  memcpy (matrixA, matrixC, SIZEOF_MATRIX);
  return *stack;
}

MatrixStack *translate(float x, float y, float z)
{
  float matrix[16];
  int i;
  
  // Set all matrix elements to zero
  memset (matrix, 0, SIZEOF_MATRIX);

  // Set elements in the last column.
  matrix[index (3,0)] = x;
  matrix[index (3,1)] = y;
  matrix[index (3,2)] = z;

  // Set diagonal elements.
  for (i = 0; i < 4; i++)
  {
    matrix[index (i,i)] = 1;
  }

  // Multiply the matrix with that on the top of the stack.
  return multMatrix (matrix);
}

MatrixStack *scale(float x, float y, float z)
{
  float matrix[16];
 
  // Set all elements to zero.
  memset (matrix, 0, SIZEOF_MATRIX);

  // Set the diagonal elements
  matrix[index (0,0)] = x;
  matrix[index (1,1)] = y;
  matrix[index (2,2)] = z;
  matrix[index (3,3)] = 1;

  // Multiply the matrix with that on the top of the stack.
  return multMatrix (matrix);
}

MatrixStack *rotate(float degree, int x, int y, int z)
{
  float matrix[16];
  float angle = degree * 3.1416 / 180;
 
  // Set elements to zero.
  memset (matrix, 0, SIZEOF_MATRIX);
  matrix[15] = 1.0;

  if (x)
  {
    matrix[index (0,0)] = 1.0;
    matrix[index (1,1)] = cos (angle); 
    matrix[index (1,2)] = sin (angle); 
    matrix[index (2,1)] = -sin (angle); 
    matrix[index (2,2)] = cos (angle);
  }
  else if (y) 
  {
    matrix[index (0,0)] = cos (angle); 
    matrix[index (0,2)] = -sin (angle); 
    matrix[index (1,1)] = 1.0;
    matrix[index (2,0)] = sin (angle);
    matrix[index (2,2)] = cos (angle);
  } 
  else if (z) 
  {
    matrix[index (0,0)] = cos (angle); 
    matrix[index (0,1)] = sin (angle);
    matrix[index (1,0)] = -sin (angle); 
    matrix[index (1,1)] = cos (angle);
    matrix[index (2,2)] = 1.0;
  }

  // Multiply the matrix with that on the top of the stack.
  return multMatrix (matrix);
}

Vertex globalVertex (Vertex a)
{
  float *matrix = mStack->topMatrix;
  float w;
  w = a.x * matrix[index(0,3)] + a.y * matrix[index(1,3)] + 
      a.z * matrix[index(2,3)] + matrix[index(3,3)];

  if (w == 0)
  {
    w = 1;
  }

  return vertex ((a.x * matrix[index(0,0)] + a.y * matrix[index(1,0)] +
                  a.z * matrix[index(2,0)] + matrix[index(3,0)]) / w,
                 (a.x * matrix[index(0,1)] + a.y * matrix[index(1,1)] + 
                  a.z * matrix[index(2,1)] + matrix[index(3,1)]) / w, 
                 (a.x * matrix[index(0,2)] + a.y * matrix[index(1,2)] +
                  a.z * matrix[index(2,2)] + matrix[index(3,2)]) / w);
}
  
Vertex eyeVertex (Vertex a)
{
  float *matrix = pStack->topMatrix;
  float w;
  w = a.x * matrix[index(0,3)] + a.y * matrix[index(1,3)] + 
      a.z * matrix[index(2,3)] + matrix[index(3,3)];

  if(w == 0)
  {
    w = 1;
  }

  return vertex((a.x * matrix[index(0,0)] + a.y * matrix[index(1,0)] + 
                 a.z * matrix[index(2,0)] + matrix[index(3,0)]) / w,
                (a.x * matrix[index(0,1)] + a.y * matrix[index(1,1)] +
                 a.z * matrix[index(2,1)] + matrix[index(3,1)]) / w, 
                (a.x * matrix[index(0,2)] + a.y * matrix[index(1,2)] +
                 a.z * matrix[index(2,2)] + matrix[index(3,2)]) / w);
}

