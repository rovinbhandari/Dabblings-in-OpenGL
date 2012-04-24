/* This file declares the Cuboid class and its methods */
#ifndef CUBOID_INCLUDED
#define CUBOID_INCLUDED

#include <Polygon.h>
#include <vector>

using std::vector;

class Cuboid 
{
  public:
    Cuboid (const Pt3D& centerPoint, const double& length, 
            const double& breadth, const double& height );

  private:
    vector<Polygon> faces;
};

#endif  // end of file
