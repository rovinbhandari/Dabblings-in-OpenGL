// vi: autoindent:nu:ts=8:noexpandtab
/* File that defines the functions required for vector calculus */

#include <cmath>

double dotProduct (double vector1[], double vector2[])
{
	double retVal = 0;
	for (int i = 0, retVal = 0; i < 3; i++)
	{
		retVal += vector1[i] * vector2[i]; 
	}

	return retVal;
}

double magnitude (double vector[])
{
	return sqrt ( dotProduct (vector, vector));
}

void findUnitVector (double vector[], double unitVector[])
{
	double mag = magnitude (vector);

	for (int i = 0; i < 3; i++)
	{
		unitVector[i] = vector[i] / mag;
	}
}	
