/* Program to create a cube using point cloud */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void display (void)
{
	glEnable ( GL_DEPTH_TEST );
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   // Set drawing color
   glColor3f (1.0, 1.0, 1.0);

/*   float i, j, k;
 
   gluLookAt (-1, 0.5 , -0.3, 0, 0, 0, 0, 1, 0);

   glBegin (GL_POINTS);
   for ( i = -0.5; i <= 0.5; i += 0.01)
   {
      for ( j = -0.5; j <= 0.5; j += 0.001 )
      {
         for ( k = -0.5; k <= 0.5; k += 0.01)
         {
            glVertex3f (i, j, k);
         }
      }
   }
   glEnd ();
   */

   gluLookAt (0.3, 0.3, 0.3, 0, 0, 0, 0, 0, 1);
   glutSolidCone (.5, 1.0, 30, 30);

   glFlush ();
}

int main (int argc, char * argv[])
{
   glutInit (&argc, argv);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowPosition (20, 60);
   glutInitWindowSize (360, 360);
   glutCreateWindow (argv[0]);

   glutDisplayFunc (&display); 

   glutMainLoop ();

   return 0;
}
