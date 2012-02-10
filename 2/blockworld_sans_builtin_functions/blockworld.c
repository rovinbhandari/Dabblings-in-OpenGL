#include <blockworld.h>

#define TOLERANCE 0.0001

static bwCD __bwCuboidDimensions__ = {0.2d, 02.d, 0.2d};
static size_t __sizebwCD__ = sizeof(bwCD);

static GLdouble __bwCuboidVertices__[8][3];
static GLdouble __bwCuboidNormals__[6][3] =
   {
      {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
   };
static GLint __bwCuboidFaces__[6][4] =
   {
      {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
      {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
   };

static bwCD* __bwDimensions__(GLdouble l, GLdouble b, GLdouble h);
static void __bwInit__(bwCD* dims);
static void __bwCuboid__(void);
static GLdouble __bwHCF__(GLdouble a, GLdouble b);
static GLboolean __bwCompareDouble__(GLdouble a, GLdouble b);

void bwTranslate(GLdouble i, GLdouble j, GLdouble k)
{
   const GLdouble tm[] =
            {
               1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               i, j, k, 1
            };
   glMultMatrixd(tm);
}

void bwScale(GLdouble i, GLdouble j, GLdouble k)
{
   const GLdouble tm[] =
            {
               i, 0, 0, 0,
               0, j, 0, 0,
               0, 0, k, 0,
               0, 0, 0, 1
            };
   glMultMatrixd(tm);
}

void bwCuboid(GLdouble l, GLdouble b, GLdouble h)
{
   __bwInit__(__bwDimensions__(l, b, h));
   __bwCuboid__();
}

void bwCube(GLdouble e)
{
   bwCuboid(e, e, e);
}


void bwCuboid2(GLdouble l, GLdouble b, GLdouble h)
{
   GLdouble minedge = __bwHCF__(__bwHCF__(l, b), h), i, j, k;
   for(i = 0.0d; i < l; i += minedge)
      for(j = 0.0d; j < h; j += minedge)
         for(k = 0.0d; k < b; k += minedge)
         {
            glPushMatrix();
            bwTranslate(i, j, k);
            bwCube(minedge);
            glPopMatrix();
         }
}

void bwSphere(GLdouble r, GLdouble e)
{
   GLdouble max_boundary = r + 2 * e, i, j, k, dist, maxradius, minradius;
   for(i = -1 * max_boundary * e; i <= max_boundary * e; i += e)
      for(j = -1 * max_boundary * e; j <= max_boundary * e; j += e)
         for(k = -1 * max_boundary * e; k <= max_boundary * e; k += e)
         {
            dist = sqrt(i * i + j * j + k * k);
            maxradius = r * e + e / 2;
            minradius = r * e - e / 2;
            if(dist > minradius && dist <= maxradius)
            {
               glPushMatrix();
               bwTranslate(i, j, k);
               bwCube(e);
               glPopMatrix();
            }
         }
}

void bwCylinder(GLdouble r, GLdouble h, GLdouble e)
{
   GLdouble max_boundary = r + 2 * e, i, j, k, dist, maxradius, minradius;
   for(i = -1 * max_boundary * e; i <= max_boundary * e; i += e)
      for(j = -1 * max_boundary * e; j <= max_boundary * e; j += e)
         for(k = 0.0d; k <= h * e; k += e)
         {
            dist = sqrt(i * i + j * j);
            maxradius = r * e + e / 2;
            minradius = r * e - e / 2;
            if(k > 2 * e && k < (h - 2) * e)
            {
               if(dist > minradius && dist <= maxradius)
               {
                  glPushMatrix();
                  bwTranslate(i, j, k);
                  bwCube(e);
                  glPopMatrix();
               } 
            }
            else
            {
               if(dist <= maxradius)
               {
                  glPushMatrix();
                  bwTranslate(i, j, k);
                  bwCube(e);
                  glPopMatrix();
               }
            }
         }
}

static bwCD* __bwDimensions__(GLdouble l, GLdouble b, GLdouble h)
{
   bwCD* x = (bwCD*) malloc(__sizebwCD__);
   x->length = l;
   x->breadth = b;
   x->height = h;
   return x;
}

static void __bwInit__(bwCD* dims)
{
   memcpy(&__bwCuboidDimensions__, dims, __sizebwCD__);
   __bwCuboidVertices__[0][0] = 0.0d;
   __bwCuboidVertices__[0][1] = 0.0d;
   __bwCuboidVertices__[0][2] = __bwCuboidDimensions__.breadth;
   __bwCuboidVertices__[1][0] = 0.0d;
   __bwCuboidVertices__[1][1] = 0.0d;
   __bwCuboidVertices__[1][2] = 0.0d;
   __bwCuboidVertices__[2][0] = 0.0d;
   __bwCuboidVertices__[2][1] = __bwCuboidDimensions__.height;
   __bwCuboidVertices__[2][2] = 0.0d;
   __bwCuboidVertices__[3][0] = 0.0d;
   __bwCuboidVertices__[3][1] = __bwCuboidDimensions__.height;
   __bwCuboidVertices__[3][2] = __bwCuboidDimensions__.breadth;
   __bwCuboidVertices__[4][0] = __bwCuboidDimensions__.length;
   __bwCuboidVertices__[4][1] = 0.0d;
   __bwCuboidVertices__[4][2] = __bwCuboidDimensions__.breadth;
   __bwCuboidVertices__[5][0] = __bwCuboidDimensions__.length;
   __bwCuboidVertices__[5][1] = 0.0d;
   __bwCuboidVertices__[5][2] = 0.0d;
   __bwCuboidVertices__[6][0] = __bwCuboidDimensions__.length;
   __bwCuboidVertices__[6][1] = __bwCuboidDimensions__.height;
   __bwCuboidVertices__[6][2] = 0.0d;
   __bwCuboidVertices__[7][0] = __bwCuboidDimensions__.length;
   __bwCuboidVertices__[7][1] = __bwCuboidDimensions__.height;
   __bwCuboidVertices__[7][2] = __bwCuboidDimensions__.breadth;
}

static void __bwCuboid__(void)
{
   int i;
   for(i = 0; i < 6; i++)
   {
      glBegin(GL_QUADS);
      glNormal3dv(__bwCuboidNormals__[i]);
      glVertex3dv(__bwCuboidVertices__[__bwCuboidFaces__[i][0]]);
      glVertex3dv(__bwCuboidVertices__[__bwCuboidFaces__[i][1]]);
      glVertex3dv(__bwCuboidVertices__[__bwCuboidFaces__[i][2]]);
      glVertex3dv(__bwCuboidVertices__[__bwCuboidFaces__[i][3]]);
      glEnd();
   }
}

static GLdouble __bwHCF__(GLdouble a, GLdouble b)
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

static GLboolean __bwCompareDouble__(GLdouble a, GLdouble b)
{
   if ( a <= 1.1 * b || a >= 0.9 * b)
      return GL_TRUE;
   else
      return GL_FALSE;
}

