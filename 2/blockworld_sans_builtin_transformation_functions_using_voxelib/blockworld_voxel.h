#ifndef BLOCKWORLD_VOXEL
#define BLOCKWORLD_VOXEL

#include <GL/gl.h>


/* Function to construct a cuboid using voxel method (internally).
 * The domain for the recursive partitioning is set to the 'size' of a
 * cube of edge of maximum of the edges of the cuboid.
 * The cube is constructed such that (x_min, y_min, z_min) = (0,0,0)
 */
void bwVoxelCuboid (GLdouble length, GLdouble breadth, GLdouble height);

#endif  // End of file
