#include <stdio.h>

typedef struct CuboidDimensions
	{
		double length;
		double breadth;
		double height;
	}
	CD;

class Cuboid
{
	private:
		CD Dimensions;
		double Normals[6][3];
		double Vertices[8][3];
		int Faces[6][4];
	public:
		Cuboid(CD*);
		void Rotate();
		void Translate();
		void Scale();
}
