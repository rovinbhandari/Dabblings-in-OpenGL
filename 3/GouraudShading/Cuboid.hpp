#ifndef CUBOID_HPP
#define CUBOID_HPP

enum AXIS {X, Y, Z, NONE};

typedef struct CuboidDimensions
	{
		double length;
		double height;
		double breadth;
	}
	CD;

class Cuboid
{
	private:
		CD Dimensions;
		double Normals[6][3];
		int Faces[6][4];
		double Vertices[8][3];
		double Colour[3];

		void RotateY(double);
	
	public:
		Cuboid(CD&);
		void SetColour(double []);
		void GetColour(double []);
		void Rotate(int, double);
		void Translate(double, double, double);
		void Scale(double, double, double);
		void GetNormals(int, double [][3]);
		void GetVertex(int, double []);
		void GetVertices(int, int []);
};

#endif
