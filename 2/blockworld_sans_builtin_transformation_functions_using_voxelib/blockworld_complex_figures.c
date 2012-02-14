#include <blockworld.h>
#include <blockworld_voxel.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>
#include <common.h>
#include <voxel.h>

#define DIFF 0.1
#define SHELTER_DIFF 0.05
#define WINDOW_BORDER 0.1
#define ROOF_EXT 0.08
#define B_FACTOR 1.4

#define LTE(x,e) ((x<e) && vlCmpDouble (x,e)) 
#define GTE(x,e) ((x>e) && vlCmpDouble (x,e))

GLdouble view_angle = 0;

#define VOXEL_LEN_TEST(x,y,z,length,voxel_size,func) \
do\
{\
  if ( length > 2 * voxel_size )\
  {\
    GLint i;\
    GLdouble new_x, new_y, new_z, new_length;\
    new_length = length / 2;\
    \
    for ( i = 0; i < N_CHILDREN; i++)\
    {\
        new_x = x + ((i / 4) % 2) * new_length;\
        new_y = y + ((i / 2) % 2) * new_length;\
        new_z = z + (      i % 2) * new_length;\
    \
        func (new_x, new_y, new_z, new_length);\
    }\
    return; \
  }\
}\
while(0)  

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

GLdouble voxel_size;

int bwHouse_ (double x, double y, double z, double length)
{
  
  VOXEL_LEN_TEST (x, y, z, length, voxel_size, bwHouse_);

  /* Check if the point lies in the first cuboid area */
  if (   ( x >= 0 && x <= base1)
      && ( y >= 0 && y <= height_cuboid1)
      && ( z >= 0 && z <= base1) )
  {
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid1_texture);
    vlPutVoxelAt (x, y, z, voxel_size);
  }
#define Y_EXPR (y - height_cuboid1)
#define ROOF_X ( (x - (Y_EXPR) + SHELTER_DIFF >= 0 )\
              && (x  <= (base1 + base2_l + SHELTER_DIFF - (Y_EXPR))))
#define ROOF_Y ( (y >= height_cuboid1) && (y <= height_cuboid1 + height_pyramid))
#define ROOF_Z ( (z + SHELTER_DIFF >= 0 )\
              && (z  <= (base1 + SHELTER_DIFF - (Y_EXPR))))
  else if ( (ROOF_X) && (ROOF_Y) && (ROOF_Z) )
  {
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pyramid_texture);
    vlPutVoxelAt (x, y, z, voxel_size);
    //bwRoof (base1 + base2_l, base1 + 3 * SHELTER_DIFF, height_pyramid, 0.05);
  }
  /* Check for second cube */
  else if (   ( x >= base1 && x <= base1 + base2_l ) 
           && ( y >= 0 && y <= height_cuboid2)
           && ( z >= 0 && z <= base1 ) )
  {
    // Create the second cuboid
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cuboid2_texture);
    vlPutVoxelAt(x, y, z, voxel_size);
  }

#define DOOR_KNOB_X  (( x >= (base1 / 2 - door_width / 3))\
                  && ( x <= (base1 / 2 - door_width / 3) + door_knob_size))
#define DOOR_KNOB_Y  (( y >= door_height / 2)\
                  && ( y <= door_height / 2 + door_knob_size))
#define DOOR_KNOB_Z  (( z >= base1 + 1.3* DIFF)\
                  && (z <= base1 + 1.3 * DIFF + door_knob_size))
  // Door knob
  else if  ( (DOOR_KNOB_X) && (DOOR_KNOB_Y) && (DOOR_KNOB_Z) )
  {
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, knob_texture);
    vlPutVoxelAt (x, y, z, voxel_size);
  }

#define CHIMNEY_X ((x >= 2 * base1) && ( x <= 2 * base1 + chimney_base) )
#define CHIMNEY_Y ( (y >= height_cuboid2)\
                &&  (y <= height_cuboid2 + chimney_height))
#define CHIMNEY_Z ( (z >= base2_l / 3) && (z <= base2_l / 3 + chimney_base) ) 
  // Create a chimney
  else if ( CHIMNEY_X && CHIMNEY_Y && CHIMNEY_Z )
  {
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, chimney_texture);
    vlPutVoxelAt (x, y, z, voxel_size);
  }

}

void bwHouse (void)
{
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


  // Create house using Voxels. 
  voxel_size = vlGetVoxelSize ();
  bwHouse_ (0, 0, 0, max (base1 + base2_l, height_cuboid1 + height_pyramid));

  // Create a rectangle (as door)
  GLdouble z_deviation = base1 + DIFF;
  glBegin (GL_POLYGON);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, door_texture);
  glVertex3f (door_width/2  + base1/2, 0 + DIFF,z_deviation);
  glVertex3f (door_width/2  + base1/2, door_height, z_deviation);
  glVertex3f (-door_width/2 + base1/2, door_height, z_deviation);
  glVertex3f (-door_width/2 + base1/2, 0 + DIFF, z_deviation);
  glEnd ();

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
#define RESET_VAL() road_texture[0] = road_texture[1] = road_texture[2] = \
                    RANDGRAY;
#define PRINT_VALS() printf ("%g %g %g\n", road_texture[0], road_texture[1], road_texture[2]);                    


GLdouble road_length, road_width, road_height;
static GLfloat road_texture[] = {0.3, 0.3, 0.3, 1};
GLdouble block_length = 0.15;

void bwRoad_ (GLdouble x, GLdouble y ,GLdouble z, GLdouble length)
{
  
  VOXEL_LEN_TEST (x, y, z, length, block_length, bwRoad_);

  printf ("%g %g %g %g : %g %g %g\n", x, y, z, length, road_length, road_height, road_width);
  if (   ( x >= 0) && (x <= road_length)
      && ( y >= 0) && (y <= road_height)
      && ( z >= 0) && (z <= road_width))
  {
    printf ("Rendering at %g %g %g\n");
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, road_texture);
    vlPutVoxelAt (x, y, z, length);
    RESET_VAL ();
  }
}

void bwRoad (GLdouble length, GLdouble width, GLdouble height)
{
  vlInit (block_length);
  road_length = length;
  road_width  = width;
  road_height = height;

  bwRoad_ (0, 0, 0, max (max (length, width), height));
}


