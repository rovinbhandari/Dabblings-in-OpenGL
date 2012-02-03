#include <blockworld.h>

#define TOLERANCE 0.0001

/*
GLdouble eyex = 6.0;
GLdouble eyey = 6.0;
GLdouble eyez = 6.0;
*/

/*
GLfloat viewangle;
*/

static GLdouble edge = 0.2;

/*
static GLboolean bwCmpDouble(GLdouble a, GLdouble b)
{
   if ( a <= 1.1 * b || a >= 0.9 * b)
      return GL_TRUE;
   else
      return GL_FALSE;
}
*/

static GLdouble bwHCFd(GLdouble a, GLdouble b)
{
   GLdouble t;
   while(fabs(b - 0.0d) > TOLERANCE)
   {
      t = b;
      b = fmod(a, b);
      a = t;
   }
   return a;
}

/*
void bwCubeletInit_glut(GLdouble blockedgelength)
{
   edge = blockedgelength;
}
*/

/*
void bwCubelet_glut(void)
{
   glutSolidCube(edge);
}
*/

static GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
static GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
static GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };

void bwCubeletInit_gl(GLdouble blockedgelength)
{
   edge = blockedgelength;
   /*
   v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
   v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
   v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
   v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
   v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
   v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
   */
   v[0][0] = 0;
   v[0][1] = 0;
   v[0][2] = blockedgelength;
   v[1][0] = 0;
   v[1][1] = 0;
   v[1][2] = 0;
   v[2][0] = 0;
   v[2][1] = blockedgelength;
   v[2][2] = 0;
   v[3][0] = 0;
   v[3][1] = blockedgelength;
   v[3][2] = blockedgelength;
   v[4][0] = blockedgelength;
   v[4][1] = 0;
   v[4][2] = blockedgelength;
   v[5][0] = blockedgelength;
   v[5][1] = 0;
   v[5][2] = 0;
   v[6][0] = blockedgelength;
   v[6][1] = blockedgelength;
   v[6][2] = 0;
   v[7][0] = blockedgelength;
   v[7][1] = blockedgelength;
   v[7][2] = blockedgelength;
}

void bwCubelet_gl(void)
{
   int i;
   for (i = 0; i < 6; i++) 
   {
      glBegin(GL_QUADS);
      glNormal3fv(n[i]);
      glVertex3fv(v[faces[i][0]]);
      glVertex3fv(v[faces[i][1]]);
      glVertex3fv(v[faces[i][2]]);
      glVertex3fv(v[faces[i][3]]);

      glEnd();
   }
}

/*
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
               bwCubelet_gl();
               glPopMatrix();
            }
         }
      }
   }
}
*/

/*
void bwCuboidHollow_gllen(GLdouble l, GLdouble b, GLdouble h)
{
   bwCuboidHollow_units(l / edge, b / edge, h / edge);
}
*/

/*
void bwCubeHollow_units(GLdouble units)
{
   bwCuboidHollow_units(units, units, units);
}
*/

/*
void bwCubeHollow_gllen(GLdouble len)
{
   bwCubeHollow_units(len / edge);
}
*/

void bwCubeSolid_gllen(GLdouble len)
{
   GLdouble tempedge = edge;
   bwCubeletInit_gl(len);
   bwCubelet_gl();
   edge = tempedge;
}

/*
void bwCubeSolid_units(GLdouble units)
{
   bwCubeSolid_gllen(units * edge);
}
*/

/*
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
*/

void bwCuboidSolid_gllen(GLdouble l, GLdouble b, GLdouble h)
{
   GLdouble tempedge = edge, minedge = bwHCFd(bwHCFd(l, b), h);
   
   bwCubeletInit_gl(minedge);
   
   GLdouble i, j, k;
   for(i = 0.0d; i < l; i += minedge)
   {
      for(j = 0.0d; j < h; j += minedge)
      {
         for(k = 0.0d; k < b; k += minedge)
         {
            /*
	    if( bwCmpDouble (i, (l - 1) * minedge) 
             || bwCmpDouble (j, (h - 1) * minedge) 
             || bwCmpDouble (k, (b - 1) * minedge)
             || bwCmpDouble (i, 0.0d) 
             || bwCmpDouble (j, 0.0d) 
             || bwCmpDouble (k, 0.0d) )  // rendering only the visible layer of the cube.
            {*/
               glPushMatrix();
               bwTranslate(i, j, k);
               bwCubelet_gl();
               glPopMatrix();
            /*}*/
         }
      }
   }
   
   edge = tempedge;
}

