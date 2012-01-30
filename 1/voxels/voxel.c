#include <voxel.h>

#define LENedge   1.0d

GLdouble eyex = 6.0;
GLdouble eyey = 6.0;
GLdouble eyez = 6.0;

GLfloat viewangle;

void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display_init (void)
{
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void display_voxel (void)
{
   display_init ();
   
   GLfloat cube_mat[] = 
   {0.1, 0.1, 0.1, 1};
   
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
   glutSolidCube(LENedge);
   glPopMatrix ();

}

void display_cube (void)
{
   display_init ();
   GLfloat cube_mat[] = 
   {0.1, 0.1, 0.1, 1};

   GLdouble i, j, k;
   int l;
   for(i = 0.0d; i < MAXedge * LENedge; i += LENedge)
   {
      for(j = 0.0d; j < MAXedge * LENedge; j += LENedge)
      {
         cube_mat[0] += 0.03;
         cube_mat[1] += 0.03;
         cube_mat[2] += 0.03;
         /*
         for(l = 0; l < 4; l++)
            printf("%f\n", (float) cube_mat[l]);
         */
         for(k = 0.0d; k < MAXedge * LENedge; k += LENedge)
         {
            if(i == (MAXedge - 1) * LENedge || j == (MAXedge - 1) * LENedge || k == (MAXedge - 1) * LENedge || i == 0.0d || j == 0.0d || k == 0.0d)   // rendering only the visible layer of the cube.
            {
               glPushMatrix ();
               glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
               glTranslated(i, j, k);
               glutSolidCube(LENedge);
               glPopMatrix ();
            }
         }
      }
   }

   glutSwapBuffers();
}


