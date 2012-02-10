#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define bwTranslate(i, j, k) glTranslated(i, j, k)

#define bwRotate(a, i, j, k) glRotated(a, i, j, k)

typedef struct bwCuboidDimensions
      	{
	      	GLdouble length;
		      GLdouble breadth;
      	   GLdouble height;
	      }
   	   bwCD;

bwCD* bwDimensions(GLdouble, GLdouble, GLdouble);

void bwCuboid(GLdouble, GLdouble, GLdouble);
void bwCube(GLdouble);

