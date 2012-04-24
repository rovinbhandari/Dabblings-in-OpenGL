/* This file contains the definition of the pipeline transformation functions.*/

#include <pipelineFunctions.h>
#include <sstream>

#define X_INCR 0.01
#define Y_INCR 0.01

typedef map<Pt2D, pair<double, Color> >Buffers;

using std::make_pair;
using std::stringstream;

double computeZ (double x, double y, const Polygon& polygon)
{
  return (-polygon.A() * x - polygon.B() * y + polygon.D()) * 1.0/polygon.C();
}

Buffers polygonBuffers (const Polygon& polygon)
{
  Buffers buffers;
  double x, y, z;

  for ( x = polygon.xmin(); x < polygon.xmax(); x += X_INCR)
  {
    for ( y = polygon.ymin(); y < polygon.ymax(); y += Y_INCR)
    {
      z = computeZ (x, y, polygon);
      if (polygon.contains (Pt3D (x,y,z)))
      {
/*      std::cerr << "Color : " << polygon.getColor().r << ","
                << polygon.getColor().g << ","
                << polygon.getColor().b << "\n";*/
        buffers[Pt2D (x,y)] = make_pair (z, polygon.getColor());
      }
    }
  }
  
  return buffers;
}

RefreshBuffer depthBufferMethod (const list<Polygon>& polygons)
{
  RefreshBuffer refreshBuffer;
  DepthBuffer depthBuffer;

  RefreshBuffer::iterator refreshBufferItr;
  DepthBuffer::iterator depthBufferItr;

  list<Polygon>::const_iterator itr;
  for (itr = polygons.begin(); itr != polygons.end(); itr++)
  {
    const Buffers pBuffers = polygonBuffers(*itr);
    Buffers::const_iterator pbItr;   // polygon buffers Iterator

    for (pbItr = pBuffers.begin(); pbItr != pBuffers.end(); pbItr++)
    {
      if ( (depthBufferItr = depthBuffer.find(pbItr->first)) != 
                                                      depthBuffer.end() )
      {
/*        std::cerr << "x : " << pbItr->first.x << " , y : " << pbItr->first.y
                  << " znew : " << depthBufferItr->second << ", zold : " << pbItr->second.first
                  << "\n";*/
        // If the height of the new polygon is greater than that of stored
        // height, refresh the depth and refresh buffer.
        if ( pbItr->second.first > depthBufferItr->second)
        {
          depthBufferItr->second = pbItr->second.first;
          refreshBuffer[pbItr->first] = pbItr->second.second;
        }
      }
      else
      { 
        // point doesn't already exist in the table. Add it to the table.
        depthBuffer[pbItr->first] = pbItr->second.first;
        refreshBuffer[pbItr->first] = pbItr->second.second;
      }
    }
  }

  return refreshBuffer;
}

Matrixd multiplyMatrices (const Matrixd& m1, const Matrixd& m2)
{
  int rows1 = m1.size();
  int cols1 = m1[0].size();

  int rows2 = m2.size();
  int cols2 = m2[0].size();

  // Check basic condition for matrix multiplication
  if ( rows2 != cols1)
  {
    return (Matrixd());
  }

  // Initialize an empty output matrix
  Matrixd outputMatrix;
  int i;
  for ( i = 0; i < rows1; i++)
  {
    outputMatrix.push_back (vector<double> (cols2,0));  
  }

  int j,k;
  // Perform actual multiplication
  for ( i = 0; i < rows1; i++)
  {
    for ( j = 0; j < cols2; j++)
    {
      for (k = 0; k < rows2; k++)
      {
        outputMatrix[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }

  return outputMatrix;
}

Pt3D transform (const Pt3D& p, const Matrixd& transformation)
{
  // Construct a column vector (matrix) of p.
  Matrixd ptMatrix;
  ptMatrix.push_back (vector<double> (1, p.x));
  ptMatrix.push_back (vector<double> (1, p.y));
  ptMatrix.push_back (vector<double> (1, p.z));
  ptMatrix.push_back (vector<double> (1, 1));

  // Return the point formed after applying the transformation */
  return Pt3D (multiplyMatrices (transformation, ptMatrix)[0]);
}


Pt3D world2view (const Pt3D& point, const Vector& eyeAt, const Vector& up,
                  const Vector& viewNormal)
{
#define MATRIX_SIZE 4
  
  // Construct a column vector (matrix) of p.
  Matrixd ptMatrix;
  ptMatrix.push_back (vector<double> (1, point.x));
  ptMatrix.push_back (vector<double> (1, point.y));
  ptMatrix.push_back (vector<double> (1, point.z));
  ptMatrix.push_back (vector<double> (1, 1));

  // Construct the translation matrix.
  Matrixd translation;

  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    translation.push_back (vector<double> (MATRIX_SIZE, 0));
    translation[i][i] = 1;
  }
  translation[0][3] = -eyeAt.X();
  translation[1][3] = -eyeAt.Y();
  translation[2][3] = -eyeAt.Z();

  /* Construct Rotation matrix */
  // First calculate vectors that are required for the matrix
  Vector n   = viewNormal.normalized();
  Vector tmp = up % n; // Cross product
  Vector u   = tmp / tmp.magnitude();
  Vector v   = n % u;
  
  // Construct the matrix
  Matrixd rotation;
  vector <double> t (4,0);
  // First row
  t[0] = u.X(); t[1] = u.Y(); t[2] = u.Z();
  rotation.push_back (t);
  // Second row
  t[0] = v.X(); t[1] = v.Y(); t[2] = v.Z();
  rotation.push_back (t);
  // Third row
  t[0] = n.X(); t[1] = n.Y(); t[2] = n.Z();
  rotation.push_back (t);
  //Fourth row
  t[3] = 1;
  rotation.push_back (t);

  // Multiply the matrices
  return Pt3D (multiplyMatrices ( multiplyMatrices (rotation, translation),
                                  ptMatrix)[0]);
}

string Matrixd2String (const Matrixd& m)
{
  int i, j;
  stringstream output;
  for ( i = 0; i < m.size(); i++)
  {
    for ( j = 0; j < m[i].size(); j++)
    {
      output << m[i][j] << ( j != m[i].size() - 1 ? "\t" : "");
    }
    output << "\n";
  }

  return output.str();
}
