#include <octree.h>
#include <stdio.h>
#include <math.h>
#include <voxel.h>
#include <assert.h>

// Function pointer
int (*func) (double, double, double);

// Voxel edge length
double voxel_edge;

void set_voxel_edge (double edge)
{
   voxel_edge = edge;  
}

double get_voxel_edge ()
{
   return voxel_edge;
}

void set_function_ptr (int (*func_ptr) (double, double, double))
{
   func = func_ptr;
}


/* Function to test if a node is a leaf-node */
unsigned char is_leaf ( octree_t * node)
{
	return ((node->type == LEAF) ? 1 : 0);
}

/* Function to test if a list of nodes are ALL leaf nodes */
unsigned char all_leaves (octree_t *nodes[], unsigned int size)
{
	unsigned int i;

	for ( i = 0; i < size; i++)
	{
		if ( ! is_leaf (nodes[i]))
		{
			return 0;
		}
	}

	return 1;
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

      if (all_filled && all_leaves (children, N_CHILDREN))
      {
         // All the children are filled, remove them and set the type to LEAF
         for ( i = 0; i < N_CHILDREN; i++)
         {
            assert (children[i]);      // Redundant
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
   
   if ( !tree)
   {
      exit(2);
   }
   assert (tree);
   

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
//		printf ("Voxel exists at %f %f %f of size %f\n", tree->point.x, tree->point.y, tree->point.z, tree->length);
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

void put_voxels_implementation (octree_t *tree)
{
   if ( !tree)
   {
      return;
   }
   if (LEAF == tree->type)
   {
      vlPutVoxelAt (tree->point.x, tree->point.y, tree->point.z, tree->length);
   }
   else
   {
      int i;
      for ( i = 0; i < N_CHILDREN; i++)
      {
         put_voxels_implementation (tree->children[i]);
      }
      
   }
}

void putVoxels (octree_t *tree)
{
   vlInit (voxel_edge);

   put_voxels_implementation (tree);
}

#include <assert.h>

void printTree (octree_t *tree, unsigned int level)
{
   assert (octree_file);

   unsigned int tmp = level;

   while (tmp--)
   {
      fprintf (octree_file, "\t");
   }

   if (tree)
   {
      fprintf (octree_file, "(%g,%g,%g) -- %g\n", tree->point.x, tree->point.y, tree->point.z, tree->length);
   }
   else
   {
      fprintf (octree_file, "Empty\n");
      return;
   }

   fflush (octree_file);

//   fprintf (stderr, "Printing %x\n", tree);
   if ( LEAF != tree->type )
   {
      for (tmp = 0; tmp < N_CHILDREN; tmp++)
      {
         printTree (tree->children[tmp], level+1);
      }  
   }
}
