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
  int i;

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
  int i;
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
  int i;

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
  int i;
 
  // Set all elements to zero.
  memset (matrix, 0, SIZEOF_MATRIX);

  // Set the diagonal elements
  matrix[0] = x;
  matrix[5] = y;
  matrix[10] = z;
  matrix[15] = 1;

  // Multiply the matrix with that on the top of the stack.
  return multMatrix (matrix);
}

MatrixStack *rotate(float degree, int x, int y, int z)
{
  float m[16];
  float angle = degree * 3.1416 / 180;
  int i;
 
  for(i = 0; i < 15; i++)
  {
    m[i] = 0;
  }
  m[15] = 1.0;

  if (x)
  {
    m[0] = 1.0;
    m[5] = cos (angle); 
    m[6] = sin (angle); 
    m[9] = -sin (angle); 
    m[10] = cos (angle);
  }
  else if (y) 
  {
    m[0] = cos (angle); 
    m[2] = -sin (angle); 
    m[5] = 1.0;
    m[8] = sin (angle);
    m[10] = cos (angle);
  } 
  else if (z) 
  {
    m[0] = cos (angle); 
    m[1] = sin (angle);
    m[4] = -sin (angle); 
    m[5] = cos (angle);
    m[10] = 1.0;
  }

  // Multiply the matrix with that on the top of the stack.
  return multMatrix (m);
}

Vertex globalVertex (Vertex a)
{
  float *m = mStack->topMatrix;
  float w;
  w = a.x * m[3] + a.y * m[7] + a.z * m[11] + m[15];
  if (w == 0)	w = 1;
  return vertex ((a.x * m[0] + a.y * m[4] + a.z * m[8] + m[12]) / w,
                 (a.x * m[1] + a.y * m[5] + a.z * m[9] + m[13]) / w, 
                 (a.x * m[2] + a.y * m[6] + a.z * m[10] + m[14]) / w);
}
  
Vertex eyeVertex (Vertex a)
{
  float *m = pStack->topMatrix;
  float w;
  w=a.x * m[3] + a.y * m[7] + a.z * m[11] + m[15];
  if(w==0)
  {
    w = 1;
  }
  return vertex((a.x * m[0] + a.y * m[4] + a.z * m[8] + m[12]) / w,
                (a.x * m[1] + a.y * m[5] + a.z * m[9] + m[13]) / w, 
                (a.x * m[2] + a.y * m[6] + a.z * m[10] + m[14]) / w);
}

