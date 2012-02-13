#include <blockworld_voxel.h>
#include <voxel.h>

static inline max (GLdouble a, GLdouble b)
{
  return (a > b) ? a : b ;
}

GLdouble cuboid_length, cuboid_breadth, cuboid_height;

int bwCuboidFunc (GLdouble x, GLdouble y, GLdouble z)
{

  if (   ( x >= 0 && x <= cuboid_length)
      && ( y >= 0 && y <= cuboid_height)
      && ( z >= 0 && z <= cuboid_breadth) )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void bwVoxelCuboid (GLdouble length, GLdouble breadth, GLdouble height)
{
  cuboid_length  = length;
  cuboid_breadth = breadth;
  cuboid_height  = height;

  GLdouble domain_size = max (max (length, breadth), height);

  vlSetFunction (&bwCuboidFunc);
  vlVoxel (0, 0, 0, domain_size);
}



