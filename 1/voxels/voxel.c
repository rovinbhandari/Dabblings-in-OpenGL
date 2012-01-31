#include <voxel.h>

#define LENedge   1.0d
#define MAXedge 2  

GLdouble eyex = 6.0;
GLdouble eyey = 6.0;
GLdouble eyez = 6.0;

GLfloat viewangle;

GLdouble edge = 1.0;

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
   GLfloat cube_mat[] = 
   {0.1, 0.1, 0.1, 1};

//   units = MAXedge;  

   GLdouble i, j, k;
   for(i = 0.0d; i < units * edge; i += edge)
   {
      for(j = 0.0d; j < units * edge; j += edge)
      {
         cube_mat[0] += 0.03;
         cube_mat[1] += 0.03;
         cube_mat[2] += 0.03;
         /*
         for(l = 0; l < 4; l++)
            printf("%f\n", (float) cube_mat[l]);
         */
         for(k = 0.0d; k < units * edge; k += edge)
         {
            if(i == (units - 1) * edge || j == (units - 1) * edge || k == (units - 1) * edge || i == 0.0d || j == 0.0d || k == 0.0d)   // rendering only the visible layer of the cube.
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
