// vi: autoindent:nu:ts=8:noexpandtab
/* This file contains the declaration of functions required for Gouraud shading */
#ifndef GOURAUD_SHADING
#define GOURAUD_SHADING


/* Function to construct a polygon given the vertices. 
 * This function generates a face given its vertices and the intensities at those 
 * points.
 */
void constructFace (double vertices[][3], double intensities[][3]);

/* Function to calculate intensity at a point 
 * This function takes as argument the position of light and the finalIntensity
 * array that is populated with the values. The finalIntensity array is a 
 * 1d vector for RGB valuess.
 */
void calculateIntensity (double vertex[], double normalVector[] ,double lightSource[], double eyePosition[], double initialIntensity[], double finalIntensity[]);


// Intensities using different reflection models.
void ambientLightIntensity (double initialIntensity[], double finalIntensity[]);
void specularReflectionIntensity (double initialIntensity[], double reflectionVector[], double viewVector[], double finalIntensity[]);
void diffusedReflectionIntensity (double initialIntensity[], double normalVector[], double lightUnitVector[], double finalIntensity[]);


/* Get functions for coefficients */
double getAmbientCoefficient  ();
double getSpecularCoefficient ();
double getDiffusionCoefficient();

/* Set functions for coefficients */
void setAmbientCoefficient  (double val);
void setSpecularCoefficient (double val);
void setDiffusionCoefficient(double val);

#endif // End of file.
