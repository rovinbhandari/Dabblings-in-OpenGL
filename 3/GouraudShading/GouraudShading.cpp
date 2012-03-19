// vi: autoindent:nu:ts=8:noexpandtab

#include <GouraudShading.hpp>
#include <cstring>
#include <GL/glut.h>
#include <GL/gl.h>

/* Function to calculate the average normal at a point 
 * This function requires two arguments. One is an array of normals and another
 * is the array where the average normal is stored. 
 */
void avgNormal (int normals[][3], int avgNormal[3])
{
	// It is assumed that a cuboid is used. Hence only 3 faces are involved.

	memset (avgNormal, 0, 3);

	for ( int j, i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			avgNormal[j] += (normals[i][j]/3);
		}
	}
}

/* Function to construct a polygon given the vertices. 
 * This function generates a face given its vertices and the intensities at those 
 * points.
 */
void constructFace (double vertices[4][3], double intensities[4][3])
{
	glBegin (GL_POLYGON);	
	glColor3dv  (intensities[0]);
	glVertex3dv (vertices[0]);
	glColor3dv  (intensities[1]);
	glVertex3dv (vertices[1]);
	glColor3dv  (intensities[2]);
	glVertex3dv (vertices[2]);
	glColor3dv  (intensities[3]);
	glVertex3dv (vertices[3]);
	glEnd ();
}
