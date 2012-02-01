#include <octree.h>


#define N_CHILDREN 8

// Function pointer
int (*func) (int, int, int);

// Voxel edge length
double voxel_edge;


int test_function (point_t *ptr)
{
   /* TODO : Complete this function */
   return 1;
}

void voxel_set_edge (double edge)
{
   voxel_edge = edge;  
}

void set_function_ptr (int (*func_ptr) (int, int, int))
{
   func = func_ptr;
}

octree_t * create_octree (point_t *ref_point, double length)
{
   octree_t *children[N_CHILDREN] = { (octree_t *) NULL };

   int i;
   char type;

   if ( length >= 2 * voxel_edge )
   {
      point_t new_ref_point;
      double new_length = length / 2;
      unsigned char all_filled = 1;

      for ( i = 0; i < N_CHILDREN; i++)
      {
         /* Following statement generate apt permutation of the new points */
         new_ref_point.x = ref_point->x + ( (i / 4) % 2) * new_length;
         new_ref_point.y = ref_point->y + ( (i / 2) % 2) * new_length;
         new_ref_point.z = ref_point->z +      (i   % 2) * new_length;

         if ( NULL == (children[i] = create_octree (&new_ref_point , new_length)))
         {
            all_filled = 0;
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
      }
   }
   else
   {
      // Test to see this element lies inside the given volume
      if ( test_function (ref_point))
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

   for ( i = 0; i < N_CHILDREN && type != LEAF; i++)
   {
      tree->children[i] = children[i];
   }

   return tree;
}
