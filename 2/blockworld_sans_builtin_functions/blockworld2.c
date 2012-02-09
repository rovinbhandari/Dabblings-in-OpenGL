#include <blockworld2.h>

#define TOLERANCE 0.0001

static bwCD __bwCuboidDimensions__ = {0.2d, 02.d, 0.2d};
static size_t __sizebwCD__ = sizeof(bwCD);

// Will be filled in with X,Y,Z vertexes.
static GLdouble __bwCuboidVertices__[8][3];

// Normals for the 6 faces of a cube.
static GLdouble __bwCuboidNormals__[6][3] =
   {
      {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
   };

// Vertex indices for the 6 faces of a cube.
static GLint __bwCuboidFaces__[6][4] =
   {
      {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
      {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
   };

bwCD* bwDimensions(GLdouble l, GLdouble b, GLdouble h)
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

void bwCuboid(GLdouble l, GLdouble b, GLdouble h)
{
   __bwInit__(bwDimensions(l, b, h));
   __bwCuboid__();
}

void bwCube(GLdouble e)
{
   bwCuboid(e, e, e);
}

