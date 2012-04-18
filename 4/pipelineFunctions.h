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

map<Pt2D,Color> depthBufferMethod (const list<Polygon>& polygon);

#endif	// End of file
