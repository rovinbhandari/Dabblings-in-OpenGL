#include <Polygon.h>
#include <iostream>
#include <pipelineFunctions.h>
#include <list>
#include <cstdlib>  // required for rand() 
#include <ctime>    // required for time()

using std::list;

#define MAT_SIZE 3

// Function to test Multiplication
void testMultiplication (void)
{
  Matrixd m1, m2;

  // Test with a zero matrices.
  int i;
  for ( i = 0; i < MAT_SIZE; i++)
    m1.push_back (vector<double> (MAT_SIZE,0));
  for ( i = 0; i < MAT_SIZE; i++)
    m2.push_back (vector<double> (MAT_SIZE,0));

  std::cout << "Product of \n" << Matrixd2String (m1);
  std::cout << "and \n" << Matrixd2String (m2);
  std::cout << "Resultant matrix is \n" << Matrixd2String (multiplyMatrices (m1, m2));


  // Test with a identity matrix and zero
  for ( i = 0; i < MAT_SIZE; i++)
  {
    m1[i][i] = 1;
  }
  std::cout << "Product of \n" << Matrixd2String (m1);
  std::cout << "and \n" << Matrixd2String (m2);
  std::cout << "Resultant matrix is \n" << Matrixd2String (multiplyMatrices (m1, m2));

  // Test with both identity matrices
  for ( i = 0; i < MAT_SIZE; i++)
  {
    m2[i][i] = 1;
  }
  std::cout << "Product of \n" << Matrixd2String (m1);
  std::cout << "and \n" << Matrixd2String (m2);
  std::cout << "Resultant matrix is \n" << Matrixd2String (multiplyMatrices (m1, m2));

  srand (time (NULL));
  // Test with one arbitrary and one identity matrix
  int j;
  for ( i = 0; i < MAT_SIZE; i++)
  {
    for ( j = 0; j < MAT_SIZE; j++)
    {
      m2[i][j] = rand() % 10;
    }
  }
  std::cout << "Product of \n" << Matrixd2String (m1);
  std::cout << "and \n" << Matrixd2String (m2);
  std::cout << "Resultant matrix is \n" << Matrixd2String (multiplyMatrices (m1, m2));

  // Try multiplying in the opposite order (should be same)
  std::cout << "Product of \n" << Matrixd2String (m2);
  std::cout << "and \n" << Matrixd2String (m1);
  std::cout << "Resultant matrix is \n" << Matrixd2String (multiplyMatrices (m2, m1));

  // Make the other matrix arbitrary as well and try multiplying them.
  for ( i = 0; i < MAT_SIZE; i++)
  {
    for ( j = 0; j < MAT_SIZE; j++)
    {
      m1[i][j] = rand() % 10;
    }
  }
  std::cout << "Product of \n" << Matrixd2String (m1);
  std::cout << "and \n" << Matrixd2String (m2);
  std::cout << "Resultant matrix is \n" << Matrixd2String (multiplyMatrices (m1, m2));
}

int main (void)
{
  testMultiplication ();
/*	vector<Pt3D> vertices;
  Color c;
  c.r = c.g = c.b = 1;
	
	vertices.push_back(Pt3D());
	vertices.push_back(Pt3D(1,0,0));
	vertices.push_back(Pt3D(1,1,0));
	vertices.push_back(Pt3D(0,1,0));

	Polygon t (vertices, Vector (0,0,1));
  t.setColor (c);
	std::cerr << "Polygon 1 ready\n";

  c.r = c.g = c.b = 0;
	vertices.clear();
	vertices.push_back(Pt3D(0,0,-1));
	vertices.push_back(Pt3D(1,0,-1));
	vertices.push_back(Pt3D(1,1,-1));
	vertices.push_back(Pt3D(0,1,-1));

	Polygon u (vertices, Vector(0,0,1));
  u.setColor (c);
	std::cerr << "Polygon 2 ready\n";

	list<Polygon> l;
	l.push_back(u);
	l.push_back(t);

	map<Pt2D,Color> depth = depthBufferMethod (l);
  map<Pt2D,Color>::iterator itr;
  for (itr = depth.begin(); itr != depth.end(); itr++)
  {
    std::cerr << itr->first.x  << "," << itr->first.y << "  -- "
              << itr->second.r << ","
              << itr->second.g << ","
              << itr->second.b << "\n";
  }
  std::cerr << "Buffer\n";
*/

  
	return 0;
}
