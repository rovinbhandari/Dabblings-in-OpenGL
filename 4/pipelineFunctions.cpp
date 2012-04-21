/* This file contains the definition of the pipeline transformation functions.*/

#include <pipelineFunctions.h>

#define X_INCR 0.1
#define Y_INCR 0.1

typedef map<Pt2D, pair<double, Color> >Buffers;

using std::make_pair;

double computeZ (double x, double y, const Polygon& polygon)
{
  return (-polygon.A() * x - polygon.B() * y - polygon.D()) * 1.0/polygon.C();
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
      buffers[Pt2D (x,y)] = make_pair (z, polygon.getColor());
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
