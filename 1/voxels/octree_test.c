/* Main program for testing octree implementation */

#include <octree.h>
#include <common.h>

int test_function_sphere (double x, double y, double z)
{
   double radius = 3;

   if ( x*x + y*y + z*z <= radius*radius )
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int main (int argc, char *args[])
{
   octree_t *tree;

   /* Define the domain */
   point_t ref_point;

   ref_point.x = 0;
   ref_point.y = 0;
   ref_point.z = 0;
   
   double length = 3;


   /* Set voxel edge */
   set_voxel_edge (0.5);

   /* Set the function pointer */
   set_function_ptr ( &test_function_sphere);

   tree = construct_octree (&ref_point, length);

   return 0;
}
