#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define bwTranslate(i, j, k) glTranslated(i, j, k)

#define bwRotate(a, i, j, k) glRotated(a, i, j, k)

void bwCubeletInit_glut(GLdouble blockedgelength);

void bwCubelet_glut(void);

void bwCuboidSolid_units(GLdouble l, GLdouble b, GLdouble h);
void bwCuboidHollow_units(GLdouble l, GLdouble b, GLdouble h);
void bwCuboidSolid_gllen(GLdouble l, GLdouble b, GLdouble h);
void bwCuboidHollow_gllen(GLdouble l, GLdouble b, GLdouble h);

void bwCubeHollow_units(GLdouble units);
void bwCubeHollow_gllen(GLdouble len);
void bwCubeSolid_gllen(GLdouble len);
void bwCubeSolid_units(GLdouble units);

