/* Header file for voxels library */
#ifndef VOXEL_H_INCLUDED
#define VOXEL_H_INCLUDED

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>


void vlInit (GLdouble voxel_size);
void vlVoxel ();

void vlCube  (GLdouble units);
void vlCylinder (GLdouble radius, GLdouble height);
void vlSphere (GLdouble radius);
#endif   // End of file
