#include <blockworld.h>

GLdouble eyex = 6.0;
GLdouble eyey = 6.0;
GLdouble eyez = 6.0;

GLfloat viewangle;

static GLdouble edge = 0.2;

static GLboolean bwCmpDouble(GLdouble a, GLdouble b)
{
   if ( a <= 1.1 * b || a >= 0.9 * b)
      return GL_TRUE;
   else
      return GL_FALSE;
}

void bwCubeletInit_glut(GLdouble blockedgelength)
{
   edge = blockedgelength;
}

void bwCubelet_glut(void)
{
   glutSolidCube(edge);
}

void bwCuboidHollow_units(GLdouble l, GLdouble b, GLdouble h)
{
   GLdouble i, j, k;
   for(i = 0.0d; i < l * edge; i += edge)
   {
      for(j = 0.0d; j < h * edge; j += edge)
      {
         for(k = 0.0d; k < b * edge; k += edge)
         {
            if( bwCmpDouble (i, (l - 1) * edge) 
             || bwCmpDouble (j, (h - 1) * edge) 
             || bwCmpDouble (k, (b - 1) * edge)
             || bwCmpDouble (i, 0.0d) 
             || bwCmpDouble (j, 0.0d) 
             || bwCmpDouble (k, 0.0d) )  // rendering only the visible layer of the cube.
            {
               glPushMatrix();
               bwTranslate(i, j, k);
               bwCubelet_glut();
               glPopMatrix();
            }
         }
      }
   }
}

void bwCuboidHollow_gllen(GLdouble l, GLdouble b, GLdouble h)
{
   bwCuboidHollow_units(l / edge, b / edge, h / edge);
}

void bwCubeHollow_units(GLdouble units)
{
   bwCuboidHollow_units(units, units, units);
}

void bwCubeHollow_gllen(GLdouble len)
{
   bwCubeHollow_units(len / edge);
}

void bwCubeSolid_gllen(GLdouble len)
{
   glutSolidCube(len);
}

void bwCubeSolid_units(GLdouble units)
{
   bwCubeSolid_gllen(units * edge);
}

void bwCuboidSolid_units(GLdouble l, GLdouble b, GLdouble h)
{
   GLdouble tempedge = edge;
   if(l < b && l < h)
      edge = l;
   else if(b < l && b < h)
      edge = b;
   else if(b < l && h < b)
      edge = h;
   
   GLdouble i, j, k;
   for(i = 0.0d; i < l * edge; i += edge)
   {
      for(j = 0.0d; j < h * edge; j += edge)
      {
         for(k = 0.0d; k < b * edge; k += edge)
         {
            if( bwCmpDouble (i, (l - 1) * edge) 
             || bwCmpDouble (j, (h - 1) * edge) 
             || bwCmpDouble (k, (b - 1) * edge)
             || bwCmpDouble (i, 0.0d) 
             || bwCmpDouble (j, 0.0d) 
             || bwCmpDouble (k, 0.0d) )  // rendering only the visible layer of the cube.
            {
               glPushMatrix();
               bwTranslate(i, j, k);
               bwCubeSolid_units(1);
               glPopMatrix();
            }
         }
      }
   }
   
   edge = tempedge;
}

void bwCuboidSolid_gllen(GLdouble l, GLdouble b, GLdouble h)
{
   bwCuboidSolid_units(l * edge, b * edge, h * edge);
}

