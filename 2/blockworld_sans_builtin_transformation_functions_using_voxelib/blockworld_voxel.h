#ifndef BLOCKWORLD_VOXEL
#define BLOCKWORLD_VOXEL

#include <GL/gl.h>


/* Function to set the length, breadth and height for the voxel_cuboid
 * function.
 */
void set_cuboid_edges (GLdouble length, GLdouble breadth, GLdouble height);

/*
 * Function that returns 1 if the given (x,y,z) lies inside the cuboid
 * of length 'cuboid_length', breadth 'cuboid_breadth' and height 
 * 'cuboid_height' with (x_min, y_min, z_min) = (0, 0, 0)
 */
int voxel_cuboid (GLdouble x, GLdouble y, GLdouble z);

#endif  // End of file
