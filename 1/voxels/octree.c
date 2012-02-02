#include <octree.h>
#include <stdio.h>
#include <math.h>

FILE * debug_file;

#define N_CHILDREN 8

// Function pointer
int (*func) (double, double, double);

// Voxel edge length
double voxel_edge;


/* Function to test if a cube (voxel) should exist (be placed) in a volume. 
 * The ref_point is the reference point, it is the point with the minimum x, 
 * minimum y and minimum z of the cubical volume. 
 */
int test_function (point_t *ref_point, double length)
{
   /* This function tests if 'any' of the vertices lie in volume specified by
    * the function 
    */

   int i;
   double x, y, z;

   for (i = 0; i < N_CHILDREN; i++)
   {
      x = ref_point->x + ((i / 4) % 2) * length;
      y = ref_point->y + ((i / 2) % 2) * length;
      z = ref_point->z + (      i % 2) * length;

      if ( func (x, y, z) )
         return 1;
   }
	
   return 0;
}

void set_voxel_edge (double edge)
{
   voxel_edge = edge;  
}

unsigned int closest_power_of_2 (unsigned int n)
{
	/* returns the closest power of 2 to that number.
	 * Function is similar to the ceil function on integers. 
	 * If the given number is itself a power of 2, the number is returned
	 * otherwise the next power of 2 is returned.
	 */

	if ( 1 == n)
	{
		return 2;
	}
	
	 double log_val = log2 (n);
	 
	 // if it is a whole number, then it is a power of 2
	 if ( (unsigned int) log_val == log_val )
	 {
	 	return n;
	 }
	 else
	 {
	 	return (1 << ( (unsigned int)log_val + 1));
	 }

}
void set_function_ptr (int (*func_ptr) (double, double, double))
{
   func = func_ptr;
}

octree_t * create_octree (point_t *ref_point, double length)
{
//	debug_file = fopen ("debug", "a");
//	printf ("Creating octree with length = %f\n", length);
	
   octree_t *children[N_CHILDREN] = { (octree_t *) NULL };

   int i;
   char type = NODE; 

   if ( length > voxel_edge )
   {
      point_t new_ref_point;
      double new_length = length / 2;
      unsigned char all_filled  = 1;
		unsigned char none_filled = 1;

      for ( i = 0; i < N_CHILDREN; i++)
      {
         /* Following statement generate apt permutation of the new points */
         new_ref_point.x = ref_point->x + ( (i / 4) % 2) * new_length;
         new_ref_point.y = ref_point->y + ( (i / 2) % 2) * new_length;
         new_ref_point.z = ref_point->z +      (i   % 2) * new_length;

//			printf ("Testing for point (%f %f %f)\n", new_ref_point.x, new_ref_point.y, new_ref_point.z);

         if ( NULL == (children[i] = create_octree (&new_ref_point , new_length)))
         {
            all_filled = 0;
         }

			if ( children[i] && none_filled)
			{
				none_filled = 0;
			}
      }

      if (all_filled)
      {
         // All the children are filled, remove them and set the type to LEAF
         for ( i = 0; i < N_CHILDREN; i++)
         {
            free (children[i]);
            children[i] = NULL;
         }

			type = LEAF;
      }
		if (none_filled)
		{
			// If none of the octants of the parent is filled, the function doesn't 
			// exist inside the function.
			return NULL;
		}
   }
   else
   {
      // Test to see this element lies inside the given volume
      if ( test_function (ref_point, length))
      {
         type = LEAF;
      }
      else
      {
         return NULL;
      }
   }

   octree_t *tree;
   ALLOC_TREE (tree);

   tree->point.x = ref_point->x;
   tree->point.y = ref_point->y;
   tree->point.z = ref_point->z;

   tree->length = length;
	tree->type   = type;

   for ( i = 0; i < N_CHILDREN && type != LEAF; i++)
   {
      tree->children[i] = children[i];
   }

/*	if ( LEAF == type )
	{
		printf ("Voxel exists at %f %f %f of size %f\n", tree->point.x, tree->point.y, tree->point.z, tree->length);
	}
*/
   return tree;
}

octree_t * construct_octree (point_t *ref_point, double length)
{
	/* Wrapper function for create_octree
	 * So that the length can be converted into 2^k * voxel_length
	 * such that the new_length is greater than or equal to that passed.
	 */

	int k = closest_power_of_2 (length /voxel_edge);

	return (create_octree (ref_point, k * voxel_edge));
	
}


