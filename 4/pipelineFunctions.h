/* This file contains the declarations of the pipeline transformation functions. */
#ifndef PIPELINE_INCLUDE
#define PIPELINE_INCLUDE

#include <map>
#include <list>
#include <Polygon.h>

using std::map;
using std::list;
using std::pair;

typedef map<Pt2D,double> DepthBuffer ;
typedef map<Pt2D,Color> RefreshBuffer;

/* This function requires a list of polygons and it calculates the color 
 * at 2D points. The function returns a map of Pt2D->Color. */
RefreshBuffer depthBufferMethod (const list<Polygon>& polygons);

#endif	// End of file
