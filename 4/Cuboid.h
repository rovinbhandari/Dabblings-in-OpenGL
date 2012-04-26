/* This file declares the Cuboid class and its methods */
#ifndef CUBOID_INCLUDED
#define CUBOID_INCLUDED

#include <Polygon.h>
#include <vector>
#include <list>

using std::vector;
using std::list;

class Cuboid 
{
  public:
    // Constructors
    Cuboid (const Pt3D& point, const double& length = 1, 
            const double& breadth = 1, const double& height = 1, const Color& c = Color (1,1,1));

    // Public methods
    list<Polygon> toPolygonList (void);
    void applyViewTransformation (const Pt3D& eyeAt, const Vector& up,
                                  const Vector& viewNormal);
  private:
    vector<Polygon> faces;
};

#endif  // end of file
