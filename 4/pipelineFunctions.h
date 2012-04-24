/* This file contains the declarations of the pipeline transformation functions. */
#ifndef PIPELINE_INCLUDE
#define PIPELINE_INCLUDE

#include <map>
#include <list>
#include <string>
#include <Polygon.h>

using std::map;
using std::list;
using std::pair;
using std::string;

typedef map<Pt2D,double> DepthBuffer ;
typedef map<Pt2D,Color> RefreshBuffer;
/* Matrix : Column vector of rows (each is a vector) */
typedef vector<vector <double> > Matrixd;

/* This function requires a list of polygons and it calculates the color 
 * at 2D points. The function returns a map of Pt2D->Color. */
RefreshBuffer depthBufferMethod (const list<Polygon>& polygons);

/* Function to apply any transformation on a point.
 * The function expects as input the point on which the transformation has
 * to be applied and the transformation matrix
 * The transformation matrix needs to be a 4 * 4 matrix (this is assumed)
 * The matrix is constructed as Matrixd, i.e. vector <vector <double> >.
 * Hence, the transformation should be a 'column' vector of 4 'row' vectors
 * each holding 4 values.
 *
 * This function basically returns the (transformation x [p.x p.y p.z 1]')
 * where T' implies the transform of matrix T. 
 */
Pt3D transform (const Pt3D& point, const Matrixd& transformation);

/* Function to multiply to matrices. 
 * It determines the size itself. Returns an empty matrix in case of 
 * error. 
 *
 * XXX : Currently the function just assumes that the input is a legal matrix
 * i.e. vector<vector<double> > is consistent with a matrix. Each row has 
 * the same number of entries.
 */
Matrixd multiplyMatrices (const Matrixd& m1, const Matrixd& m2);


/* Function to convert from world co-ordinate system to view co-ordinate.
 * It requires three inputs. The position of the eye, the up direction and
 * the normal of the viewing plane.
 */
Pt3D world2view (const Pt3D& point, const Vector& eyeAt, const Vector& up,
                 const Vector& viewNormal);
/* Function that converts a Matrixd to a string */
string Matrixd2String (const Matrixd& m);

#endif	// End of file
