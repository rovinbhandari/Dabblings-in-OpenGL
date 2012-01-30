/* Program to create a wireframe cube and torus
 * Author : Rajat Khanduja
 * Date : 30/1/12
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENedge   1.0d
#define MAXedge   4

GLdouble eyex = 6.0;
GLdouble eyey = 6.0;
GLdouble eyez = 6.0;

static GLfloat lightpos[] =
{10.f, 10.f, 10.f, 1.f};
static GLfloat lightcol[] =
{1.0,1.0,1,0};

void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27 :
         exit (0);
   }
}

GLfloat viewangle;

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
   glLightfv (GL_LIGHT0, GL_AMBIENT, lightcol);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50., 50., -50., 50., -50., 50.);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop ();

   return 0;
}
