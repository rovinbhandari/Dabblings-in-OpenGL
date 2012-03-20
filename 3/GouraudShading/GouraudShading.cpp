// vi: autoindent:nu:ts=8:noexpandtab

#include <GouraudShading.hpp>
#include <VectorCalculation.hpp>
#include <cstring>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>
#include <cstdio>

CuboidShading::CuboidShading(CD& cd) : Cuboid (cd)
{
	K_a = K_d = K_s = 1.0;
	N_s = 1;
}

/* Functions to get and set the constants */
double CuboidShading::getAmbientCoefficient ()
{
	return K_a;
}

void CuboidShading::setAmbientCoefficient (double val)
{
	K_a = val;
}

double CuboidShading::getSpecularCoefficient ()
{
	return K_s;
}

void CuboidShading::setSpecularCoefficient (double val)
{
	K_s = val;
}

double CuboidShading::getDiffusionCoefficient ()
{
	return K_a;
}

void CuboidShading::setDiffusionCoefficient (double val)
{
	K_d = val;
}

double CuboidShading::getSpecularParameter ()
{
	return N_s;
}

void CuboidShading::setSpecularParameter (double val)
{
	N_s = val;
}

/* Function to calculate the average normal at a point 
 * This function requires two arguments. One is an array of normals and another
 * is the array where the average normal is stored. 
 */
void CuboidShading::avgNormal (double normals[][3], double averageNormal[3])
{
	// It is assumed that a cuboid is used. Hence only 3 faces are involved.

	memset (averageNormal, 0, 3 * sizeof (double) );

	for ( int j, i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			averageNormal[j] += (normals[i][j]/3);
		}
	}
}

void CuboidShading::constructFace (double vertices[][3], double intensities[][3])
{
  	fprintf (stderr, "About to construct face.\n");
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
  	fprintf (stderr, "Construction Done.\n");
}

void CuboidShading::constructFace ( int faceNumber, double lightSource[], double eyePosition[], double intensityAmbient[], double intensitySource[])
{
	int verticesIndex[4];

	GetVertices (faceNumber, verticesIndex);

	double normals[3][3], vertices[4][3];
	double averageNormal[3];
	double finalIntensity[4][3];

  	fprintf (stderr, "Before entering loop.\n");
	for (int i = 0; i < 4; i++)
	{
		GetVertex (verticesIndex[i], vertices[i]);	
		GetNormals(verticesIndex[i], normals);
		avgNormal (normals, averageNormal);
		calculateIntensity (vertices[i], averageNormal, lightSource, eyePosition, intensityAmbient, intensitySource, finalIntensity[i]);
		fprintf (stderr, "in loop.\n");
	}

  	fprintf (stderr, "About to construct face.\n");
	constructFace (vertices, finalIntensity);
	return;
}

void CuboidShading::calculateIntensity (double vertex[], double normalVector[], double lightSource[], double eyePosition[], double intensityAmbient[], double intensitySource[], double finalIntensity[])
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
	ambientLightIntensity (intensityAmbient, finalIntensity);

	// Compute intensity due to specular reflection
	specularReflectionIntensity (intensitySource, reflectionVector, viewUnitVector, tmp);

	for ( i = 0; i < 3; i++)
	{
		finalIntensity[i] += tmp[i];
	}

	// Compute intensity due to diffused reflection.
	diffusedReflectionIntensity (intensitySource, normalVector, lightUnitVector, tmp);

	for ( i = 0; i < 3; i++)
	{
		finalIntensity[i] += tmp[i];
	}

	return;
}


void CuboidShading::ambientLightIntensity (double initialIntensity[3], double finalIntensity[])
{
	for ( int i = 0; i < 3; i++)
	{
		finalIntensity[i] = K_a * initialIntensity[i];
	}
}

void CuboidShading::specularReflectionIntensity (double initialIntensity[], double reflectionVector[], double viewVector[], double finalIntensity[])
{
	double cosPhi = dotProduct (reflectionVector, viewVector);
	cosPhi /= (magnitude (reflectionVector) * magnitude (viewVector));
	cosPhi = pow (cosPhi, N_s);

	for ( int i = 0; i < 3; i++)
	{
		finalIntensity[i] = (cosPhi > 0 ) ?  K_s * initialIntensity[i] * cosPhi : 0;
	}

	return;
}

void CuboidShading::diffusedReflectionIntensity (double initialIntensity[], double normalVector[], double lightUnitVector[], double finalIntensity[])
{
	double tmp = dotProduct (lightUnitVector, normalVector);
	
	for ( int i = 0; i < 3; i++)
	{
		finalIntensity[i] = (tmp > 0) ? K_d * initialIntensity[i] * tmp : 0; 
	}

	return ;
}

