#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#define N_CHILDREN 8

#include <GL/glut.h>
#include <GL/gl.h>

typedef struct
{
   double x;
   double y;
   double z;
} point_t;


double sphere_radius;
double cone_radius;
double cone_height;
double cube_edge;

// Function pointer
int (*func) (double, double, double);

// Voxel edge length
double voxel_edge;

GLdouble eyex, eyey, eyez;

GLdouble voxel_edge_len;

unsigned int closest_power_of_2 (unsigned int n);
int test_function (point_t *ref_point, double length);

int cone_function (double x, double y, double z);
int sphere_function (double x, double y, double z);
int cube_function (double x, double y, double z);
#endif // End of file
