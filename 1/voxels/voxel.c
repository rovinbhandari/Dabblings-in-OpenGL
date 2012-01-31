#include <voxel.h>
#include <math.h>

#define LENedge   1.0d

GLdouble eyex = 6.0;
GLdouble eyey = 6.0;
GLdouble eyez = 6.0;

GLfloat viewangle;

GLdouble edge = 1.0;

static GLboolean vlCmpDouble (GLdouble a, GLdouble b)
{
   if ( a <= 1.1 * b || a >= 0.9 * b)
      return GL_TRUE;
   else
      return GL_FALSE;
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

void vlVoxel ()
{
//   display_init ();
   
/*   GLfloat cube_mat[] = 
   {0.1, 0.1, 0.1, 1};
   
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
*/
//   edge = LENedge ;
   glutSolidCube(edge);
/*   glPopMatrix ();

   glutSwapBuffers (); */

}

/*void display_voxel_translated (GLdouble x, GLdouble y, GLdouble z)
{
   glPushMatrix ();
   glTranslate (x, y, z);
   display_voxel ();
   glPopMatrix ();
}*/


void vlCube (GLdouble units)
{
//   display_init ();
/*   GLfloat cube_mat[] = 
   {0.1, 0.1, 0.1, 1}; */

//   units = 2;  

   GLdouble i, j, k;
   for(i = 0.0d; i < units * edge; i += edge)
   {
      for(j = 0.0d; j < units * edge; j += edge)
      {
/*         cube_mat[0] += 0.03;
         cube_mat[1] += 0.03;
         cube_mat[2] += 0.03; */
         /*
         for(l = 0; l < 4; l++)
            printf("%f\n", (float) cube_mat[l]);
         */
         for(k = 0.0d; k < units * edge; k += edge)
         {
            if( vlCmpDouble (i, (units - 1) * edge) 
             || vlCmpDouble (j, (units - 1) * edge) 
             || vlCmpDouble (k, (units - 1) * edge)
             || vlCmpDouble (i, 0.0d) 
             || vlCmpDouble (j, 0.0d) 
             || vlCmpDouble (k, 0.0d) )  // rendering only the visible layer of the cube.
            {
               glPushMatrix ();
//              glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
               glTranslated(i, j, k);
     //          glutSolidCube(LENedge);     // Replacing with voxelib function
               vlVoxel ();
               glPopMatrix ();
            }
         }
      }
   }

//   glutSwapBuffers();
}


void vlCylinder (GLdouble radius, GLdouble height)
{
//    display_init ();
//   GLfloat cylinder_mat[] = 
//   {0.2, 0.2, 0.2, 1};

//   radius = 10;
//   height = 20;

   GLdouble max_edge = radius + 4 * edge;

   GLdouble i, j, k;
   double dist, maxradius, minradius;

   for(i = -1 * max_edge * edge; i <= max_edge * edge; i += edge)
   {
      for(j = -1 * max_edge * edge; j <= max_edge * edge; j += edge)
      {
         for(k = 0.0d; k <= height * edge; k += edge)
         {
            dist = sqrt(i * i + j * j);
            maxradius = radius * edge + edge / 2;
            minradius = (radius - 4 * edge) * edge - edge / 2;
            if(k > 2 * edge && k < (height - 2) * edge)
            {
               if(dist > minradius && dist <= maxradius)
               {
                  glPushMatrix();
                  glTranslated(i, j, k);
           //     glutSolidCube(edge);
                  vlVoxel ();
                  glPopMatrix();
               } 
            }
            else
            {
               if(dist <= maxradius)
               {
                  glPushMatrix();
                  glTranslated(i, j, k);
           //     glutSolidCube(edge);
                  vlVoxel ();
                  glPopMatrix();
               }
            }
         }
      }
   }
//   glutSwapBuffers();
}

void vlSphere (GLdouble radius)
{
//   display_init ();
/*   GLfloat cylinder_mat[] = 
   {0.2, 0.2, 0.2, 1}; */

/*   GLfloat sphere_mat[] = 
   {0.2, 0.2, 0.2, 1};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere_mat); */

//   radius = 14;
   
   GLdouble max_edge = radius + 4 * edge;

   GLdouble i, j, k;
   double dist, maxradius, minradius;
   for(i = -1 * max_edge * edge; i <= max_edge * edge; i += edge)
   {
      for(j = -1 * max_edge * edge; j <= max_edge * edge; j += edge)
      {
         for(k = -1 * max_edge * edge; k <= max_edge * edge; k += edge)
         {
            dist = sqrt(i * i + j * j + k * k);
            maxradius = radius * edge + edge / 2;
//            minradius = (radius - 2.0d) * edge - edge / 2;
            minradius = (radius - 4 * edge) * edge - edge / 2;
            if(dist > minradius && dist <= maxradius)
            {
               glPushMatrix();
               glTranslated(i, j, k);
               vlVoxel ();
         //      glutSolidCube(edge);
               glPopMatrix();
            }
         }
      }
   }

//   glutSwapBuffers();

}
