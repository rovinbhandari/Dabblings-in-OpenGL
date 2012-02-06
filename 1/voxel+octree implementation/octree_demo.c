/* Program to test the voxel library functions */


#include <octree.h>
#include <common.h>
#include <voxel.h>
#include <stdio.h>
#include <assert.h>
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

      
   static char printed = 0;

   set_voxel_edge (voxel_edge_len);
	
   // Set function for cone.
   set_function_ptr (&cone_function);

   static point_t ref_point_cone;
   ref_point_cone.x = ref_point_cone.y = -cone_radius ;
   ref_point_cone.z = 0;


   static octree_t *octree_cone;
   octree_cone = construct_octree ( &ref_point_cone, cone_height);

   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cone_mat);
   putVoxels (octree_cone);
   glPopMatrix ();



   // Set function for cone.
   set_function_ptr (&sphere_function);
   
   static point_t ref_point_sphere ;
   ref_point_sphere.x = ref_point_sphere.y = ref_point_sphere.z = -sphere_radius;
   static octree_t *octree_sphere;
   octree_sphere = construct_octree ( &ref_point_sphere, 2 * sphere_radius);

   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere1_mat);
   glTranslated (0,3,-4);
   putVoxels (octree_sphere);
   glPopMatrix ();

   // Set function for cube
   set_function_ptr (&cube_function);

   static point_t ref_point_cube ;
   ref_point_cube.x = ref_point_cube.y = ref_point_cube.z = -cube_edge/2;
   static octree_t *octree_cube;
   octree_cube = construct_octree ( &ref_point_cube, cube_edge);
   
   
   glPushMatrix ();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cube_mat);
   glTranslated (0,-10,-3);
   putVoxels (octree_cube);
   glPopMatrix ();


   glutSwapBuffers ();
   
   if (!printed)
   {
      fprintf (octree_file, "------OCTREE FOR CONE -----\n");
      printTree (octree_cone, 0);
      fprintf (octree_file, "------OCTREE FOR SPHERE -----\n");
      printTree (octree_sphere, 0);
      fprintf (octree_file, "------OCTREE FOR CUBE -----\n");
      printTree (octree_cube, 0);
   }
   printed = 1;
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
   octree_file = fopen ("octree_representation", "w");
   assert (octree_file);

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
