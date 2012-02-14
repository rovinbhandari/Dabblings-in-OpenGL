#ifndef BLOCKWORLD_COMPLEX_FIGURES
#define BLOCKWORLD_COMPLEX_FIGURES

#include <tree.h>
#include <character.h>

#define VOXEL_LEN_TEST(x,y,z,length,voxel_size,func) \
do\
{\
  if ( length > 2 * voxel_size )\
  {\
    GLint i;\
    GLdouble new_x, new_y, new_z, new_length;\
    new_length = length / 2;\
    \
    for ( i = 0; i < N_CHILDREN; i++)\
    {\
        new_x = x + ((i / 4) % 2) * new_length;\
        new_y = y + ((i / 2) % 2) * new_length;\
        new_z = z + (      i % 2) * new_length;\
    \
        func (new_x, new_y, new_z, new_length);\
    }\
    return; \
  }\
}\
while(0)  

#define PUT_VOXEL_HERE vlPutVoxelAt(x, y, z, length)

void bwHouse (void);
void bwRoad  (GLdouble length, GLdouble width, GLdouble heigth);

#define VOXEL_LEN_TEST(x,y,z,length,voxel_size,func) \
do\
{\
  if ( length > 2 * voxel_size )\
  {\
    GLint i;\
    GLdouble new_x, new_y, new_z, new_length;\
    new_length = length / 2;\
    \
    for ( i = 0; i < N_CHILDREN; i++)\
    {\
        new_x = x + ((i / 4) % 2) * new_length;\
        new_y = y + ((i / 2) % 2) * new_length;\
        new_z = z + (      i % 2) * new_length;\
    \
        func (new_x, new_y, new_z, new_length);\
    }\
    return; \
  }\
}\
while(0)  


#endif // End of file
