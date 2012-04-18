/* This file contains the declarations of the pipeline transformation functions. */
#ifndef PIPELINE_INCLUDE
#define PIPELINE_INCLUDE

#include <map>
#include <list>
#include <Polygon.h>

using std::map;
using std::list;

map<Pt3D,Color> depthBuffer (const Polygon& polygon);
map<Pt3D,Color> depthBuffer (const list<Polygon>& polygon);

#endif	// End of file
