#ifndef BLOCKWORLD_H
#define BLOCKWORLD_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

typedef struct bwCuboidDimensions
      	{
	      	GLdouble length;
		      GLdouble breadth;
      	   GLdouble height;
	      }
   	   bwCD;

GLboolean bwCompareDouble(GLdouble, GLdouble);

void bwCube(GLdouble);
void bwCuboid(GLdouble, GLdouble, GLdouble);

#endif
