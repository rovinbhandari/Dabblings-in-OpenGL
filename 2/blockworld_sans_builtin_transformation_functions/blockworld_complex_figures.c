#include <blockworld.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>

#define DIFF 0.05
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

#define COLRANDRGB       ((rand() % 501) / 1000.0f + 0.5)    // [0.5, 1.0]
#define SIZESMOKEPARTICLE      0.01d
static void bwSmokeParticle()
{
   GLfloat col = COLRANDRGB, textureleaf[] = {col, col, col, 1.0f};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textureleaf);
   bwCube(SIZESMOKEPARTICLE);
}

#define SIZESMOKECLOUD     0.4d
void bwSmoke()
{
   GLdouble i, j, k;
   for(i = 0.0d; i < SIZESMOKECLOUD; i += SIZESMOKEPARTICLE)
      for(j = 0.0d; j < SIZESMOKECLOUD; j += SIZESMOKEPARTICLE)
         for(k = 0.0d; k < SIZESMOKECLOUD; k += SIZESMOKEPARTICLE)
         {
            if((rand() % 1000) > 10)               // 1% probabilistic density
               continue;
            glPushMatrix();
            bwTranslate(i, j, k);
            bwSmokeParticle();
            glPopMatrix();
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

  static GLfloat door_texture[]    = { 0.33, 0.17, 0.03, 1};
  static GLfloat pyramid_texture[] = { 0.7, 0.3, 0.3, 1};
  static GLfloat cuboid1_texture[] = { 0.9, 0.6, 0.4, 1};
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
  bwCuboid(base1, base1, height_cuboid1);
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
  
  // Create Smoke clouds above chimney
  glPushMatrix ();
  bwTranslate ((2) * base1, height_cuboid2 + chimney_height * 1.2, base2_l / 5);
  bwSmoke();
  glPopMatrix ();
  glPushMatrix ();
  bwTranslate ((2) * base1, height_cuboid2 + chimney_height * 1.3, base2_l / 20);
  bwSmoke();
  glPopMatrix ();
  glPushMatrix ();
  bwTranslate ((2.02) * base1, height_cuboid2 + chimney_height * 1.4, 0);
  bwSmoke();
  glPopMatrix ();
}

#define RANDGRAY  (rand() % 10) / 100.0 + 0.2   //[0.2, 0.3]

/* Function to draw a single segment of road length */
void bwRoadSegment (GLdouble length, GLdouble width, GLdouble height)
{
  GLdouble cuboid_width = 0.75;
  GLdouble cur_width    = 0;

  static GLfloat road_texture[] = {0.3, 0.3, 0.3, 1};

  static char first = 1;

  if (first)
  {
    srand(time(NULL));
    first = 0;
  }

#define RESET_VAL() road_texture[0] = road_texture[1] = road_texture[2] = \
                    RANDGRAY;
#define PRINT_VALS() printf ("%g %g %g\n", road_texture[0], road_texture[1], road_texture[2]);                    

  while ( cur_width + cuboid_width <= width )
  {
    glPushMatrix ();
    bwTranslate (0, 0, cur_width);
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, road_texture);
    bwCuboid (length, cuboid_width, height);
    glPopMatrix ();
    cur_width += cuboid_width;
    RESET_VAL();
  }
}

void bwRoad (GLdouble length, GLdouble width, GLdouble height)
{
  GLdouble layer_length = 0.5;
  GLdouble cur_length   = 0; 
 
  while ( cur_length < length )
  {
    glPushMatrix ();
    bwTranslate (cur_length, 0, 0);
//    bwCuboid (layer_length, width, height);
    bwRoadSegment (layer_length, width, height);
    glPopMatrix ();
    cur_length += layer_length;
  }
}
