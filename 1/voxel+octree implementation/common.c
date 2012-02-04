#include <common.h>
#include <math.h>

#define SQR(x) (x)*(x)

unsigned char cmpDouble (double a, double b)
{
   if ( a <= 1.1 * b && a >= 0.9 * b)
      return 1;
   else
      return 0;
}

unsigned int abs (int n)
{
   return (n >= 0) ? n : -n;
}

#define LTE(x,y) ((x) < (y) || cmpDouble (x,y))

int cube_function (double x, double y, double z)
{
   double edge = 4;
   
   x = abs (x);
   y = abs (y);
   z = abs (z);

   edge = edge / 2;
   
   if ( LTE (x, edge)  && LTE (y, edge) && LTE (z, edge))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int cone_function (double x, double y, double z)
{
   double base_radius = 3;
   double height = 6;

   if ( z <= height && SQR(x) + SQR(y) <= SQR(base_radius * ( (height - z) /height)) )
      return 1;
   else
      return 0;
}

int sphere_function (double x, double y, double z)
{
   double radius = 1;

   if ( LTE ( SQR (x) + SQR (y) + SQR(z), SQR (radius)))
   {
      return 1;
   }
   else
   {
      return 0;
   }
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

