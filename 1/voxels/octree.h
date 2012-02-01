/* File contains the declaration of structures and functions required by octree
 * Author : Rajat Khanduja
 * Date  : 02/02/12
 */

#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include <stdlib.h>

typedef struct
{
   double x;
   double y;
   double z;
} point_t;
 
enum { NODE, LEAF };
 
typedef struct octree_t 
{     
   // This point is (x-min, y-min, z-min)
   point_t point;
   double length;                // Edge length
   struct octree_t *children[8];
   

   unsigned char type;
} octree_t;

#define ALLOC_TREE(ptr) ptr = (octree_t*) malloc ( sizeof (octree_t) )


// Function to set voxel's edge
void set_voxel_edge (double edge);

// Function to set function pointer
void set_function_ptr (int (*func_ptr) (int, int, int));

// Function to create octree
octree_t * create_octree (point_t *ref_point, double length);

#endif   // end of file
