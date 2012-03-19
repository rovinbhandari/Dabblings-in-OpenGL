// vi: autoindent:nu:ts=8:noexpandtab

#include <GouraudShading.hpp>
#include <cstring>

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

/* Function to construct a  */
