// vi: autoindent:nu:ts=8:noexpandtab
/* This file contains the declaration of functions required for Gouraud shading */
#ifndef GOURAUD_SHADING
#define GOURAUD_SHADING

#include <Cuboid.hpp>

class CuboidShading : public Cuboid
{
	private:
		// K_a, K_s, K_d are coeffecients for ambient, specular reflection and diffused reflection respectively. They vary from 0 to 1, where 0 means dull and 1 is bright.
		// N_s is the specular reflection parameter.
		// N_s = 0   ->  very dull
		// N_s > 100 ->  very bright
		double K_a, K_d, K_s, N_s;
	
	public:
		CuboidShading(CD& cd);

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
		void calculateIntensity (double vertex[], double normalVector[] ,double lightSource[], double eyePosition[], double intensityAmbient[], double intensitySource[], double finalIntensity[]);


		// Intensities using different reflection models.
		void ambientLightIntensity (double intensityAmbient[], double finalIntensity[]);
		void specularReflectionIntensity (double intensitySource[], double reflectionVector[], double viewVector[], double finalIntensity[]);
		void diffusedReflectionIntensity (double intensitySource[], double normalVector[], double lightUnitVector[], double finalIntensity[]);


		/* Get functions for coefficients */
		double getAmbientCoefficient  ();
		double getSpecularCoefficient ();
		double getSpecularParameter   ();
		double getDiffusionCoefficient();

		/* Set functions for coefficients */
		void setAmbientCoefficient  (double val);
		void setSpecularCoefficient (double val);
		void setSpecularParameter   (double val);
		void setDiffusionCoefficient(double val);

		void avgNormal (double normals[][3], double avgNormal[3]);

};

#endif // End of file.
