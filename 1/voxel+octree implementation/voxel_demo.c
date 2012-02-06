/* Program to test the voxel library functions */


#include <voxel.h>
#include <common.h>
#include <stdio.h>
#include <stdlib.h>

void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display (void)
{
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   vlInit (voxel_edge_len);
	
   vlSetFunction (&cone_function);

   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cone_mat);
   vlVoxel (-cone_radius, -cone_radius, 0, cone_height);
   glPopMatrix ();

   vlSetFunction(&sphere_function);
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere1_mat);
   glTranslated (0,3,-4);
   vlVoxel (-sphere_radius, -sphere_radius, -sphere_radius, 2*sphere_radius);
   glPopMatrix ();
 
 
   vlSetFunction(&cube_function);
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
   glTranslated (0, -10, -3);
   vlVoxel (-cube_edge/2, -cube_edge/2, -cube_edge/2, cube_edge);
   glPopMatrix ();
   glutSwapBuffers ();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27 :
         exit (0);
   }
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv)
{
   if (argc > 1 )
   {
      voxel_edge_len = atof (argv[1]);
      printf ("Setting voxel edge length to %g\n", voxel_edge_len);
   }
   else
   {
      printf ("No voxel length provided. Setting it to %g\n", voxel_edge_len );
   }
   
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (750, 750);               // TODO : Reference
   glutCreateWindow (argv[0]);                  // TODO : Reference
   init ();

   /* Set the display function */
   glutDisplayFunc (&display);

   /* Set the reshape function */
   glutReshapeFunc (&reshape);

   /* Set the keyboard function */
   glutKeyboardFunc (&keyboard);
   
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, lightcol);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50., 50., -50., 50., -50., 50.);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop ();

   return 0;
}
