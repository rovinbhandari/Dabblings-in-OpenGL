#include <voxel.h>
#include <math.h>
#include <common.h>

#define LENedge   1.0d

int (*func) (double, double, double);

GLfloat viewangle;

GLdouble edge = 1.0;

static GLboolean vlCmpDouble (GLdouble a, GLdouble b)
{
   if ( a <= 1.1 * b || a >= 0.9 * b)
      return GL_TRUE;
   else
      return GL_FALSE;
}

GLdouble vlGetVoxelSize ()
{
  return edge;
}

void vlInit (GLdouble voxel_size)
{
   edge = voxel_size;
}

void display_init (void)
{
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void vlPutVoxelAt (double x, double y, double z, double length)
{
   glPushMatrix ();
   glTranslated (x,y,z);
   glutSolidCube(length);
   glPopMatrix ();
}

void vlSetFunction ( int (*func_ptr) (double, double, double))
{
   func = func_ptr; 
}

void create_voxels (double x, double y, double z, double length)
{
   if ( length > edge)
   {  
      double new_x, new_y, new_z;
      double new_length = length / 2;
      int i;

      for ( i = 0; i < N_CHILDREN; i++)
      {
         new_x = x + ((i / 4) % 2) * new_length;
         new_y = y + ((i / 2) % 2) * new_length;
         new_z = z + (      i % 2) * new_length;

         create_voxels (new_x, new_y, new_z, new_length);
      }
   }
   else
   {
      point_t ref_point;
      ref_point.x = x;
      ref_point.y = y;
      ref_point.z = z;

      if ( test_function (&ref_point, length) )
      {
         vlPutVoxelAt (x, y, z, length);
      }
   }
}

void vlVoxel (double x, double y, double z, double length)
{
   unsigned int k = closest_power_of_2 ( length / edge);

   create_voxels (x, y, z, k * edge);
}
