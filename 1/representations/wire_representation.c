/* Program to create a wireframe cube and torus
 * Author : Rajat Khanduja
 * Date : 30/1/12
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>

GLdouble eyex = 6.0;
GLdouble eyey = 0.0;
GLdouble eyez = 6.0;

static GLfloat lightpos[] =
{10.f, 10.f, 10.f, 1.f};
static GLfloat sphere_mat[] =
{0.2f, .1f, 0.2f, 1.f};
static GLfloat cube_mat[] = 
{0, 1, 0, 1};
static GLfloat cube2_mat[] = 
{0.4, 0.3, 0, 1};
static GLfloat octa_mat[] =
{0.4,0.4,0.8,0};
static GLfloat cone_mat[] =
{0.8,0.4,0.0,0};
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


/* Draw a sphere */
GLfloat sphereX = 0.f, sphereY = 0.f, sphereZ = 0.f;

/* Function to draw sphere */
void make_sphere(void)
{
  glPushMatrix();
  glTranslatef(sphereX, sphereY, sphereZ);
  glCallList(1);
  glPopMatrix();

}


void display (void)
{
   /* Clear stencile each time */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   
   glLoadIdentity ();
   
   /* Set eye and viewing direction */
   gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   /* Create octahedron */
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, octa_mat);
   glTranslated (2, 0, -5);
   glutSolidOctahedron();
   glPopMatrix ();

   /* Create Wire Cone */
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cone_mat);
   glTranslated (1, 3, 2);
   glutWireCone (0.8, 2.0, 30, 30);
   glPopMatrix ();

   /* Create wire Torus */
   GLfloat torus_mat[] = {0.5, 0.5, 0, 1};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, torus_mat);
   glutWireTorus (0.5, 2.0, 30, 50);
   

   /* Create point-based Cube */
   GLfloat i, j, k; 
   GLfloat x_min, x_max;
   GLfloat y_min, y_max;
   GLfloat z_min, z_max;
   GLfloat edge_size = 2.0;
   GLfloat point_size = .5;
   GLfloat distance = 0.05;

   y_min = x_min = -5;
   z_min = -2;
   y_max = y_min + edge_size;
   x_max = x_min + edge_size;
   z_max = z_min + edge_size;
   
   memcpy (torus_mat, cube_mat, sizeof(GLfloat) * 4) ;
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, torus_mat);
   /* 
    XXX XXX :- BUG : doesn't work with 
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
     It changes the color of the Torus as well. 
    */
//   glDisable (GL_POINT_SMOOTH);
   glPointSize (point_size);
   glBegin (GL_POINTS);
//   glColor3f (1.0,0, 1.0);
   for ( i = x_min; i <= x_max; i += distance)
   {
      for ( j = y_min; j <= y_max; j += distance )
      {
         for ( k = z_min; k <= z_max; k += distance)
         {
            glVertex3f (i, j, k);
         }
      }
   }
   glEnd ();

   /* Create point based cube-interior surface */
   y_min = -3;
   x_min = -8;
   z_min = 0;
   y_max = y_min + edge_size;
   x_max = x_min + edge_size;
   z_max = z_min + edge_size;
   
   memcpy (torus_mat, cube2_mat, sizeof(GLfloat) * 4) ;
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, torus_mat);
   /* 
    XXX XXX :- BUG : doesn't work with 
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube2_mat);
     It changes the color of the Torus as well. 
    */
//   glDisable (GL_POINT_SMOOTH);
   glPointSize (point_size);
   glBegin (GL_POINTS);
//   glColor3f (1.0,0, 1.0);
   for ( i = x_min; i <= x_max; i += distance)
   {
      for ( j = y_min; j <= y_max; j += distance )
      {
         for ( k = z_min; k <= z_max; k += distance)
         {
            if ( ( i == x_min 
                || j == y_min
                || k == z_min))
            {
              glVertex3f (i, j, k);
            }

         }
      }
   }
   glEnd ();

   /* Create a sphere */
   glPushMatrix();
   glRotatef(viewangle, 0.f, 1.f, 0.f);
   glEnable(GL_DEPTH_TEST);
   make_sphere ();  
   glDisable(GL_DEPTH_TEST);
   glPopMatrix();

   glutSwapBuffers();
}

/* Not used now */
void displayWireCube (void)
{
//   displayWireInit ();
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
   glutInitWindowSize (750, 750);               // TODO : Reference
   glutCreateWindow (argv[0]);                  // TODO : Reference
   init ();

   /* Set the display function */
   glutDisplayFunc (&display);

   /* Set the reshape function */
   glutReshapeFunc (&reshape);

   /* Set the keyboard function */
   glutKeyboardFunc (&keyboard);
   

   GLUquadricObj *sphere;
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
   glLightfv (GL_LIGHT0, GL_AMBIENT, lightcol);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   /* make display lists for sphere and cone; for efficiency */

   glNewList(1, GL_COMPILE);
   sphere = gluNewQuadric();
   //glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
   gluSphere(sphere, 1.f, 100, 100);
   gluDeleteQuadric(sphere);
   glEndList();

   
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50., 50., -50., 50., -50., 50.);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop ();

   return 0;
}
