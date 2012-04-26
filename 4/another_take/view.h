#ifndef VIEW_INCLUDED
#define VIEW_INCLUDED

#include <general.h>

void setViewer(Vertex eye, Vertex lookAt, Vertex up);
void setFrustum(float w, float h, float n, float f);

#endif // end of file
