#include <Cuboid.hpp>
#include <cstring>
#include <cstdio>
#include <cstdlib>

static size_t __sizeCD__ = sizeof(CD);
static double CuboidNormals[6][3] = {
			{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
			{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
				    };
static int CuboidFaces[6][4] = {
			{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
			{4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
			       };

Cuboid::Cuboid(CD& cd)
{
	memcpy(&Dimensions, &cd, __sizeCD__);
	
	memcpy(Normals, CuboidNormals, 6 * 3 * sizeof(double));
	
	memcpy(Faces, CuboidFaces, 6 * 4 * sizeof(int));
	
	Vertices[0][0] = 0.0d;
	Vertices[0][1] = 0.0d;
	Vertices[0][2] = Dimensions.breadth;

	Vertices[1][0] = 0.0d;
	Vertices[1][1] = 0.0d;
	Vertices[1][2] = 0.0d;
	
	Vertices[2][0] = 0.0d;
	Vertices[2][1] = Dimensions.height;
	Vertices[2][2] = 0.0d;
	
	Vertices[3][0] = 0.0d;
	Vertices[3][1] = Dimensions.height;
	Vertices[3][2] = Dimensions.breadth;
	
	Vertices[4][0] = Dimensions.length;
	Vertices[4][1] = 0.0d;
	Vertices[4][2] = Dimensions.breadth;
	
	Vertices[5][0] = Dimensions.length;
	Vertices[5][1] = 0.0d;
	Vertices[5][2] = 0.0d;
	
	Vertices[6][0] = Dimensions.length;
	Vertices[6][1] = Dimensions.height;
	Vertices[6][2] = 0.0d;
	
	Vertices[7][0] = Dimensions.length;
	Vertices[7][1] = Dimensions.height;
	Vertices[7][2] = Dimensions.breadth;
}

void Cuboid::Rotate()
{
	return;
}

void Cuboid::Translate(double i, double j, double k)
{
	for(int a = 0; a < 8; a++)
	{
		Vertices[a][0] += i;
		Vertices[a][1] += j;
		Vertices[a][2] += k;
	}
}

void Cuboid::Scale(double i, double j, double k)
{
	for(int a = 0; a < 8; a++)
	{
		Vertices[a][0] *= i;
		Vertices[a][1] *= j;
		Vertices[a][2] *= k;
	}
}

void Cuboid::GetNormals(int vertex, double normals[][3])
{
	int k = 0;
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(Faces[i][j] == vertex)
				memcpy(normals[k], Normals[i], 3 * sizeof(double));
			break;
		}
		k++;
	}
}

void Cuboid::GetVertex(int vertex, double vertexvalues[3])
{
	memcpy(vertexvalues, Vertices[vertex], 3 * sizeof(double));
}
