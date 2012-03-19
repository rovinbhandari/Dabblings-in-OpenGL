// vi: autoindent:nu:ts=8:noexpandtab

#include <GouraudShading.hpp>
#include <VectorCalculus.hpp>
#include <cstring>
#include <GL/glut.h>
#include <GL/gl.h>

static double K_a = 1.0;
static double K_s = 1.0;
static double K_d = 1.0;

/* Functions to get and set the constants */
double getAmbientCoefficient ()
{
	return K_a;
}

void setAmbientCoefficient (double val)
{
	K_a = val;
}

double getSpecularCoefficient ()
{
	return K_s;
}

void setSpecularCoefficient (double val)
{
	K_s = val;
}

double getDiffusionCoefficient ()
{
	return K_a;
}

void setDiffusionCoefficient (double val)
{
	K_d = val;
}


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



void constructFace (double vertices[][3], double intensities[][3])
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

void calculateIntensity (double vertex[], double normalVector[], double lightSource[], double eyePosition[], double initialIntensity[], double finalIntensity[])
{
	// Take dot product of the vector from the lightSource to the vertex
	// with the normalVector at the vertex.
	double lightVector[3];

	
	int i;

	for ( i = 0; i < 3; i++)
	{
		lightVector[i] = lightSource[i] - vertex[i];
	}

	// Find the direction of the 'view' vector using the eyePosition.
	double viewVector[3];

	for ( i = 0; i < 3; i++)
	{
		viewVector[i] = eyePosition[i] - vertex[i];
	}

	// Find the unit vectors.
	double lightUnitVector[3];
	double viewUnitVector[3];

	findUnitVector (lightVector, lightUnitVector);
	findUnitVector (viewVector, viewUnitVector);

	// Compute the reflection vector. 
	// R = (2N.L)N - L
	
	double factor = 2 * dotProduct (normalVector, lightUnitVector);
	double reflectionVector[3];

	for ( i = 0; i < 3; i++)
	{
		reflectionVector[i] = factor * normalVector[i] - lightUnitVector[i];
	}
	
	double tmp[3];

	// Compute intensity due to ambient light
	ambientLightIntensity (initialIntensity, finalIntensity);

	// Compute intensity due to specular reflection
	specularReflectionIntensity (initialIntensity, reflectionVector, viewUnitVector, tmp);

	for ( i = 0; i < 3; i++)
	{
		finalIntensity[i] += tmp[i];
	}

	// Compute intensity due to diffused reflection.
	diffusedReflectionIntensity (initialIntensity, normalVector, lightUnitVector, tmp);

	for ( i = 0; i < 3; i++)
	{
		finalIntensity[i] += tmp[i];
	}
}


