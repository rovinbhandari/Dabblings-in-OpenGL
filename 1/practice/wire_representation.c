/* Program to create a wireframe cube and torus
 * Author : Rajat Khanduja
 * Date : 30/1/12
 */

#include <GL/glut.h>
#include <stdlib.h>


GLdouble eyex = 0.0;
GLdouble eyey = 3.0;
GLdouble eyez = 5.0;

void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27 :
         exit (0);
   }
}

void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void displayWireInit (void)
{
   /* Function that initializes for wire models */
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0,1.0,0.0);      // Drawing color yellow (RGB = (1,1,0))
}


void displayWireTorus (void)
{
   displayWireInit ();
   glLoadIdentity ();

   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glutWireTorus (0.5, 2.0, 10, 10);

   glFlush ();
}

void displayWireCube (void)
{
   displayWireInit ();
   glLoadIdentity ();      /* No matrix loaded, hence cleared*/

   /* gluLookAt (GLdouble eyex, GLdouble eyey, GLdouble eyez,
                 GLdouble atx , GLdouble aty , GLdouble atz,
                 GLdouble upx , GLdouble upy , GLdouble upz )
    */
    gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef (1.0, 2.0, 1.0);
    glutWireCube (1.0);
    glFlush ();

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
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);               // TODO : Reference
   glutCreateWindow (argv[0]);                  // TODO : Reference
   init ();

   /* Set the display function */
   glutDisplayFunc (&displayWireTorus);

   /* Set the reshape function */
   glutReshapeFunc (&reshape);

   /* Set the keyboard function */
   glutKeyboardFunc (&keyboard);

   glutMainLoop ();

   return 0;
}
