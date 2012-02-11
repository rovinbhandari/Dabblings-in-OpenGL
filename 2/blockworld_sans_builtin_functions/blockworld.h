#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define bwRotate(a, i, j, k) glRotated(a, i, j, k)

typedef struct bwCuboidDimensions
      	{
	      	GLdouble length;
		      GLdouble breadth;
      	   GLdouble height;
	      }
   	   bwCD;

void bwTranslate(GLdouble, GLdouble, GLdouble);
void bwScale(GLdouble, GLdouble, GLdouble);

void bwCube(GLdouble);
void bwCuboid(GLdouble, GLdouble, GLdouble);
void bwCuboid2(GLdouble, GLdouble, GLdouble);
void bwSphere(GLdouble, GLdouble);
void bwCylinder(GLdouble, GLdouble, GLdouble);
void bwPyramid (GLdouble, GLdouble, GLdouble);
