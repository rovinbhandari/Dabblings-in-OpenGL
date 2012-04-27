#ifndef MATRIXMANIPULATION_H
#define MATRIXMANIPULATION_H

#include <commons.h>
#include <Vertex.h>

typedef struct _MatrixStack 
{
  float topMatrix[16];
  struct _MatrixStack *prev;
} MatrixStack;


typedef enum 
{
  MODELVIEW,
  PROJECTION
} MatrixMode;

/* Function that sets MatrixMode. It takes as input a variable of type 
 * MatrixMode (essentially an int) */
void setMatrixMode(MatrixMode mode);

/* Function that returns the matrix mode.*/
int getMatrixMode();

/* Function to initialize a matrix. Returns a pointer to the stack */
MatrixStack *initMatrix ();

/* Function to push a matrix onto the stack.Returns a pointer to the top of 
 * the stack, which is the same as the pushed matrix.*/
MatrixStack *pushMatrix ();

/* Function to pop a matrix from the stack. */
MatrixStack *popMatrix ();

/* Function to multiply a matrix with the top of the stack. */
MatrixStack *multMatrix (float *matrix);

/* Function to translate the matrix on the top of the stack. Returns 
 * a pointer to the top of the stack. */
MatrixStack *translate (float x,float y,float z);

/* Function to apply scale-transformation on the matrix on the top of the
 * stack. Returns pointer to the top of the stack. */
MatrixStack *scale (float x,float y,float z);

/* Function to apply rotate-transformation on the matrix on the top of the 
 * stack. Returns pointer to the top of the stack. */
MatrixStack *rotate (float degree,int x, int y,int z);

/* Function to convert a vertex to global co-ordinates. */
Vertex globalVertex (Vertex a);

/* Function to convert a vertex to eye co-ordinates. */
Vertex eyeVertex (Vertex a);

#endif // end of file

