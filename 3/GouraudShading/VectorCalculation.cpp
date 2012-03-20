// vi: autoindent:nu:ts=8:noexpandtab
/* File that defines the functions required for vector calculus */

#include <cmath>

double dotProduct (double vector1[], double vector2[])
{
	double retVal = 0;
	for (int i = 0; i < 3; i++)
	{
		retVal += (vector1[i] * vector2[i]); 
	}

	return retVal;
}

#define SQR(x) ((x)*(x))

double magnitude (double vector[])
{
	return sqrt ( SQR(vector[0]) + SQR(vector[1]) + SQR(vector[2]));
}

void findUnitVector (double vector[], double unitVector[])
{
	double mag = magnitude (vector);

	for (int i = 0; i < 3; i++)
	{
		unitVector[i] = vector[i] / mag;
	}
}	
