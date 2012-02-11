#include <blockworld.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define DIFF 0.1

void bwHouse (void)
{
  GLdouble base1, base2_l, base2_b;
  GLdouble height_cuboid1, height_cuboid2;
  GLdouble height_pyramid;
  GLdouble door_width, door_height;
  GLdouble chimney_base, chimney_height;

  static GLfloat door_texture[]    = { 1.0, 1.0, 1.0, 1};
  static GLfloat pyramid_texture[] = { 1.0, 1.0, 0.0, 1};
  static GLfloat cuboid1_texture[] = { 0.0, 1.0, 1.0, 1};
  static GLfloat cuboid2_texture[] = { 1.0, 0.0, 1.0, 1};
  static GLfloat chimney_texture[] = { 0.4, 0.4, 0.6, 1};

  base1   =  4;
  base2_l = 5;
  base2_b = 3;
  height_cuboid1 = 7;
  height_cuboid2 = 6;
  height_pyramid = 4 ;
  door_width = 1.5;
  door_height = height_cuboid1 / 2;
  chimney_base = 0.5;
  chimney_height = 0.8;

  
  // Create one cuboid and place pyramid on top
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid1_texture);
  bwCuboid (base1, base1, height_cuboid1);
  glPushMatrix ();
  bwTranslate (0, height_cuboid1,0);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pyramid_texture);
  bwPyramid (base1, height_pyramid, 0.3);
  glPopMatrix ();

  // Create the second cuboid
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid2_texture);
  bwTranslate (base1, 0, 0);
  bwCuboid (base2_l, base1, height_cuboid2);
  glPopMatrix ();

  // Create a rectangle (as door)
  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, door_texture);
  glVertex3f (door_width/2  + base1/2, 0 + DIFF,base1 + DIFF);
  glVertex3f (door_width/2  + base1/2, door_height, base1 + DIFF);
  glVertex3f (-door_width/2 + base1/2, door_height, base1 + DIFF);
  glVertex3f (-door_width/2 + base1/2, 0 + DIFF, base1 + DIFF);
  glEnd ();

  // Create a chimney
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, chimney_texture);
  bwTranslate ((2) * base1, height_cuboid2, base2_l / 3);
  bwCuboid2 (chimney_base, chimney_base, chimney_height);
  glPopMatrix ();
  
}
