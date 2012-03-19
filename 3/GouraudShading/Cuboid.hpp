#ifndef CUBOID_HPP
#define CUBOID_HPP

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
		int Faces[6][4];
		double Vertices[8][3];
	
	public:
		Cuboid(CD&);
		void Rotate();
		void Translate(double, double, double);
		void Scale(double, double, double);
		void GetNormals(int, double [][3]);
		void GetVertex(int, double []);
};

#endif
