#include <blockworld_voxel.h>


GLdouble cuboid_length, cuboid_breadth, cuboid_height;

void set_cuboid_edges (GLdouble length, GLdouble breadth, GLdouble height)
{
  cuboid_length  = length;
  cuboid_breadth = breadth;
  cuboid_height  = height;
}


int voxel_cuboid (GLdouble x, GLdouble y, GLdouble z)
{
  if (   ( x >= 0 && x <= cuboid_length)
      || ( y >= 0 && y <= cuboid_height)
      || ( z >= 0 && z <= cuboid_breadth) )
  {
    return 1;
  }
  else
  {
    return 0;
  }
      
}
