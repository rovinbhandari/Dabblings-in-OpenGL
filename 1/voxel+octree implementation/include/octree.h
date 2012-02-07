#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <common.h>
 
enum { NODE, LEAF };
 
FILE * octree_file;

typedef struct octree_t 
{     
   // This point is (x-min, y-min, z-min)
   point_t point;
   double length;                // Edge length
   struct octree_t *children[8];
   
	// A simple node or a leaf
   unsigned char type;
} octree_t;

#define ALLOC_TREE(ptr) ptr = (octree_t*) malloc ( sizeof (octree_t) )


// Function to set voxel's edge
void set_voxel_edge (double edge);

// Function to get voxel's edge
double get_voxel_edge ();

/* Function to set function pointer
 * This function pointer should return zero if the point (x,y,z) doesn't lie
 * inside the required volume and non-zero integer, if it does */
void set_function_ptr (int (*func_ptr) (double, double, double));

/* Function to create octree
 * This function returns the pointer to an octree for a domain with (x-min, y-min, z-min)
 * defined by ref_point and length as the size of the domain. The size of the domain
 * is converted to the closest multiple of '2'.
 * The constructed octrees have the 'type' parameter set for all nodes to help decipher if it 
 * is a normal node or a leaf element. Using this information, voxels of size larger size can 
 * be placed. 
 */
octree_t * construct_octree (point_t *ref_point, double length);

void putVoxels (octree_t *tree);

void printTree (octree_t *tree, unsigned int level);

#endif   // end of file
