// vi: autoindent:nu:ts=8:noexpandtab
/* File that declares functions required for vector calculus. */
#ifndef VECTOR_CALCULUS
#define VECTOR_CALCULUS

/* Function to calculate the dot product of two vectors */
double dotProduct (double vector1[], double vector2[]);

/* Function to calculate the magnitude of a vector. */
double magnitude (double vector[]);

/* Function to take in a 'vector' and return a 'unitVector' in its direction */
void findUnitVector (double vector[], double unitVector[]);

#endif	// End of file
