#include <blockworld.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define DIFF 0.1
#define SHELTER_DIFF 0.05
#define WINDOW_BORDER 0.1
#define ROOF_EXT 0.08
#define B_FACTOR 1.4

GLdouble view_angle = 0;

static void bwRoof (GLdouble base_l, GLdouble base_b, 
                    GLdouble height, GLdouble cuboid_height)
{
  GLdouble cur_height = 0;
  GLint i = 0;
	while (height - cur_height > 0)
	{
		glPushMatrix ();
		bwTranslate ( -ROOF_EXT + (i * cuboid_height * B_FACTOR) / 2 , cur_height, 0);

		/* Using bwCuboid gives different behavior */
		if (height - cur_height > cuboid_height)
			bwCuboid( base_l + ROOF_EXT * 2, base_b, cuboid_height);
		else
			bwCuboid (base_l + ROOF_EXT * 2, base_b, (height - cur_height));

		glPopMatrix ();
		cur_height += cuboid_height;
		base_l     -= cuboid_height * B_FACTOR;
    base_b     -= cuboid_height;
    i++;
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
  GLdouble window_edge, window_height;
  GLdouble glass_edge;

  static GLfloat door_texture[]    = { 1.0, 1.0, 1.0, 1};
  static GLfloat pyramid_texture[] = { 0.7, 0.3, 0.3, 1};
  static GLfloat cuboid1_texture[] = { 0.8, 0.5, 0.2, 1};
  static GLfloat cuboid2_texture[] = { 0.7, 0.7, 0.5, 1};
  static GLfloat chimney_texture[] = { 0.3, 0.3, 0.3, 1};
  static GLfloat knob_texture[]    = { 1.0, 1.0, 0.0, 1};
  static GLfloat window_texture[]   = { 0.0, 0.0, 0.0, 1};
  static GLfloat glass_texture[]  = { 1.0, 1.0, 1.0, 1};

  base1   = 4;
  base2_l = 5;
  base2_b = 3;
  height_cuboid1 = 6;
  height_cuboid2 = 6;
  height_pyramid = 2 ;
  door_width     = 1.5;
  door_height    = height_cuboid1 / 2;
  chimney_base   = 0.5;
  chimney_height = 1.9;
  door_knob_size = 0.1;
  window_edge    = 1.8;
  window_height  = 2.5;
  glass_edge     = (window_edge - 3 * WINDOW_BORDER) / 2;
  
  // Create one cuboid and place roof on top
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid1_texture);
  //bwRectangle (base1, base1, height_cuboid1);
  bwCuboid2(base1, base1, height_cuboid1);
  glPushMatrix ();
  bwTranslate (0, height_cuboid1, 0);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pyramid_texture);
  bwRoof (base1 + base2_l, base1 + 3 * SHELTER_DIFF, height_pyramid, 0.05);
  glPopMatrix ();

  // Create the second cuboid
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid2_texture);
  bwTranslate (base1, 0, 0);
  //bwRectangle (base2_l, base1, height_cuboid2);
  bwCuboid(base2_l, base1, height_cuboid2);
  glPopMatrix ();

  // Create a rectangle (as door)
  GLdouble z_deviation = base1 + DIFF;
  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, door_texture);
  glVertex3f (door_width/2  + base1/2, 0 + DIFF,z_deviation);
  glVertex3f (door_width/2  + base1/2, door_height, z_deviation);
  glVertex3f (-door_width/2 + base1/2, door_height, z_deviation);
  glVertex3f (-door_width/2 + base1/2, 0 + DIFF, z_deviation);
  glEnd ();

  // Door knob
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, knob_texture);
  bwTranslate ( base1 / 2 - door_width /3, door_height / 2, z_deviation);
  bwCube (door_knob_size);
  glPopMatrix ();

  // Create a square as a Window
  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, window_texture);
  GLdouble x_deviation = base1 + base2_l / 2;
  GLdouble y_deviation;
  
  glVertex3f (x_deviation - window_edge / 2, window_height, z_deviation);
  glVertex3f (x_deviation - window_edge / 2, window_height + window_edge, z_deviation);
  glVertex3f (x_deviation + window_edge / 2, window_height + window_edge, z_deviation);
  glVertex3f (x_deviation + window_edge / 2, window_height , z_deviation);
  glEnd();

  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glass_texture);
  x_deviation += (-window_edge / 2) + WINDOW_BORDER;
  z_deviation += DIFF/10;
  y_deviation = window_height + WINDOW_BORDER;
  glVertex3f (x_deviation, y_deviation, z_deviation);
  glVertex3f (x_deviation, y_deviation + glass_edge, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation + glass_edge, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation , z_deviation);
  glEnd();

  glBegin (GL_POLYGON);
  y_deviation = window_height + 2 * WINDOW_BORDER + glass_edge;
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glass_texture);
  glVertex3f (x_deviation, y_deviation, z_deviation);
  glVertex3f (x_deviation, y_deviation + glass_edge - WINDOW_BORDER, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation + glass_edge - WINDOW_BORDER, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation , z_deviation);
  glEnd();

  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glass_texture);
  x_deviation += glass_edge + WINDOW_BORDER;
  y_deviation = window_height + WINDOW_BORDER;
  glVertex3f (x_deviation, y_deviation, z_deviation);
  glVertex3f (x_deviation, y_deviation + glass_edge, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation + glass_edge, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation , z_deviation);
  glEnd();

  glBegin (GL_POLYGON);
  y_deviation = window_height + 2 * WINDOW_BORDER + glass_edge;
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glass_texture);
  glVertex3f (x_deviation, y_deviation, z_deviation);
  glVertex3f (x_deviation, y_deviation + glass_edge - WINDOW_BORDER, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation + glass_edge - WINDOW_BORDER, z_deviation);
  glVertex3f (x_deviation + glass_edge, y_deviation , z_deviation);
  glEnd();

  // Create a chimney
  glPushMatrix ();
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, chimney_texture);
  bwTranslate ((2) * base1, height_cuboid2, base2_l / 3);
  bwRectangle2 (chimney_base, chimney_base, chimney_height);
  glPopMatrix (); 
  
}

