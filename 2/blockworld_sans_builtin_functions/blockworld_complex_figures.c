#include <blockworld.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define DIFF 0.2
#define SHELTER_DIFF 0.05

static void bwRoof (GLdouble base_l, GLdouble base_b, 
                    GLdouble height, GLdouble cuboid_height)
{
  GLdouble cur_height = 0;
	while (height - cur_height > 0)
	{
		glPushMatrix ();
		bwTranslate (0, cur_height, 0);

		/* Using bwCuboid gives different behavior */
		if (height - cur_height > cuboid_height)
			bwRectangle2 (base_l, base_b, cuboid_height);
		else
			bwCuboid2 (base_l, base_b, (height - cur_height));

		glPopMatrix ();
		cur_height += cuboid_height;
		base_l     -= cuboid_height;
    base_b     -= cuboid_height;
	}
}


void bwHouse (void)
{
  GLdouble base1, base2_l, base2_b;
  GLdouble height_cuboid1, height_cuboid2;
  GLdouble height_pyramid;
  GLdouble door_width, door_height;
  GLdouble chimney_base, chimney_height;
  GLdouble door_knob_size;

  static GLfloat door_texture[]    = { 1.0, 1.0, 1.0, 1};
  static GLfloat pyramid_texture[] = { 0.9, 0.4, 0.4, 1};
  static GLfloat cuboid1_texture[] = { 0.2, 0.2, 0.6, 1};
  static GLfloat cuboid2_texture[] = { 0.2, 0.6, 0.2, 1};
  static GLfloat chimney_texture[] = { 0.3, 0.3, 0.3, 1};
  static GLfloat knob_texture[]    = { 1.0, 1.0, 0.0, 1};

  base1   = 4;
  base2_l = 5;
  base2_b = 3;
  height_cuboid1 = 6;
  height_cuboid2 = 6;
  height_pyramid = 2 ;
  door_width = 1.5;
  door_height = height_cuboid1 / 2;
  chimney_base = 0.5;
  chimney_height = 1.3;
  door_knob_size = 0.1;

  
  // Create one cuboid and place roof on top
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid1_texture);
  bwRectangle2 (base1, base1, height_cuboid1);
  glPushMatrix ();
  bwTranslate (0, height_cuboid1 + 2 * SHELTER_DIFF, 0);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pyramid_texture);
  bwRoof (base1 + base2_l, base1 + 2 * SHELTER_DIFF, height_pyramid, 0.05);
  glPopMatrix ();

  // Create the second cuboid
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid2_texture);
  bwTranslate (base1, 0, 0);
  bwRectangle2 (base2_l, base1, height_cuboid2);
  glPopMatrix ();

  // Create a rectangle (as door)
  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, door_texture);
  glVertex3f (door_width/2  + base1/2, 0 + DIFF,base1 + DIFF);
  glVertex3f (door_width/2  + base1/2, door_height, base1 + DIFF);
  glVertex3f (-door_width/2 + base1/2, door_height, base1 + DIFF);
  glVertex3f (-door_width/2 + base1/2, 0 + DIFF, base1 + DIFF);
  glEnd ();

  // Door knob
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, knob_texture);
  bwTranslate ( base1 / 2 - door_width /3, door_height / 2, base1 + DIFF);
  bwCube (door_knob_size);
  glPopMatrix ();

  // Create a chimney
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, chimney_texture);
  bwTranslate ((2) * base1, height_cuboid2, base2_l / 3);
  bwRectangle2 (chimney_base, chimney_base, chimney_height);
  glPopMatrix (); 
  
}

void bwRobotBody (void)
{
  GLdouble leg_height  = 3;
  GLdouble feet_base_l, feet_base_b, feet_height;
}
