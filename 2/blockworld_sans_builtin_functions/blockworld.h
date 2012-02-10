#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define bwTranslate(i, j, k) glTranslated(i, j, k)

#define bwRotate(a, i, j, k) glRotated(a, i, j, k)

typedef struct bwCuboidDimensions
      	{
	      	GLdouble length;
		      GLdouble breadth;
      	   GLdouble height;
	      }
   	   bwCD;

void bwCube(GLdouble);
void bwCuboid(GLdouble, GLdouble, GLdouble);
void bwCuboid2(GLdouble, GLdouble, GLdouble);
void bwSphere(GLdouble, GLdouble);
void bwCylinder(GLdouble, GLdouble, GLdouble);

