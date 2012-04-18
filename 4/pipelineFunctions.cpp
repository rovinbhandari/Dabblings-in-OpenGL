/* This file contains the definitions of the pipeline transformation functions */

#include <pipelineFunctions.h>

#define X_INCR 1
#define Y_INCR 1

map<Pt3D,Color> depthBuffer (const Polygon& polygon)
{
	map<Pt2D,double> depth;
	map<Pt2D,Color> refresh;

	double x,y;
	map<Pt2D,double>::iterator  depthItr;
	map<Pt2D,Color>::iterator refreshItr;
	for ( x = polygon.xmin(), y = polygon.ymin(); 
				x < polygon.xmax() &&  y < polygon.ymax(); x += X_INCR, y += Y_INCR)
	{
		if ( (depthItr = depth.find (Pt2D(x,y))) != depth.end())
		{
			// Found in map.
		}
		else
		{
			// Doesn't already exist in map.
		}
	}
}
