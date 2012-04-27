#include <renderingfunctions.h>
#include <string.h>
#include <matrixmanipulation.h>

float *zBuffer;
float (*pointsTable)[4];
int y0min, y0max, y1min, y1max;
extern int MAX_H, MAX_W, WxH;
extern unsigned int *data;

void initDraw ()
{
  int i, j;
  zBuffer = malloc (WxH * sizeof (float));

  // Set z-buffer to 2
  for(i = 0; i < WxH; i++)
  {
    zBuffer[i] = 2;
  }
 
  // Paint the background black
  memset (data, COLBG, WxH * sizeof (unsigned int));
}   

#define iswithin(x,low,up) ((x) <= (up) && (x) >= (low))
int testValid (Vertex a)
{
  return (iswithin(a.x,-1,1) && iswithin(a.y, -1, 1) && iswithin(a.z, 0, 1));
}

void addToPointsTable (int x, int y, float z)
{
  if(pointsTable[x][0] < 0)
  {
    pointsTable[x][0] = y;
    pointsTable[x][1] = z;
    pointsTable[x][2] = y; 
    pointsTable[x][3] = z;
  } 
  else 
  {
    if(pointsTable[x][0] > y)
    {
      pointsTable[x][0] = y;
      pointsTable[x][1] = z;
    } 
    else if (pointsTable[x][2] < y)
    {
      pointsTable[x][2] = y;
      pointsTable[x][3] = z;
    }
  }
}

int clip(Vertex *a, Vertex *b)
{
  int reg_a = 0, reg_b = 0, min = -1, ret = 1;
  float x_check, y_check, z_check, param=0, max_param=1;
  
  reg_a += (a->x > 1) ? 2 : (a->x < -1) ? 1 : 0;
  reg_a += (a->y > 1) ? 8 : (a->y < -1) ? 4 : 0;
  reg_a += (a->z > 1) ? 32: (a->z < -1) ? 16: 0;

  reg_b += (b->x > 1) ? 2 : (b->x < -1) ? 1 : 0;
  reg_b += (b->y > 1) ? 8 : (b->y < -1) ? 4 : 0;
  reg_b += (b->z > 1) ? 32: (b->z < 0 ) ? 16: 0;  // Verify.
  
  if(reg_a == 0 && reg_b == 0)
  {
    return 1;
  }
  
  if((a->x == b->x) && (a->y == b->y) && (a->z == b->z))
  { 
    return 0; 
  }
  
  if ( (reg_a ^ reg_b) != 0)
  {
    return 0;
  }
  
  if (reg_a!=0)
  {
    x_check = (reg_a & 3)  == 0 ? 0  : (reg_a & 3) * 2 - 3;
    y_check = (reg_a & 12) == 0 ? 0  : (reg_a & 12) / 2 - 3;
    z_check = (reg_a & 48) == 0 ? -1 : (reg_a & 48) / 16 - 1;
    
    if (x_check) 
    { 
      param = (x_check - a->x) / (b->x - a->x); 
      if(max_param < param)
      { 
        max_param = param; 
        min = 0;
      }
    }
    
    if (y_check) 
    { 
      param = (y_check - a->y) / (b->y - a->y); 
      if (max_param < param)
      {
        max_param = param; 
        min = 1; 
      }
    }
    
    if (z_check+1)
    { 
      param = (z_check - a->z) / (b->z - a->z);
      if (max_param < param)
      {
        max_param = param; 
        min = 2; 
      }
    }
    
    if (min == 0)
    { 
      if (a->x < x_check)
      { 
        if(x_check == 1) a->x=1+.000001; a->x=-1; 
      } 
      
      if (a->x>x_check)
      { 
        if(x_check==-1) a->x=-1-.000001; a->x=1; 
      } 
    }
    else 
    {
      a->x = max_param * (b->x - a->x) + a->x;
    }
    
    if (min == 1) 
    { 
      if (a->y < y_check)
      { 
        if(y_check == 1) a->y=1+.000001; a->y=-1;
      }
      if (a->y > y_check)
      { 
        if(y_check==-1) a->y=-1-.000001; a->y=1; 
      }
    }
    else 
    {
      a->y = max_param * (b->y-a->y) + a->y;
    }
    
    if (min == 2)
    { 
      if (a->z < z_check) 
      {
        if(z_check == 1) a->z=1+.000001; a->z=0; 
      } 
      if (a->z > z_check)
      { 
        if(z_check==0) a->z=0-.000001; a->z=1; 
      } 
    }
    else 
    {
      a->z = max_param * (b->z - a->z) + a->z;
    }
    if(!testValid(*a))
    {
      return 0;
    }
    ret=2;
  }
  
  param = 0;
  max_param = 1; 
  min = -1;

  if (reg_b != 0)
  {
    x_check = (reg_b & 3) == 0  ?  0 : (reg_b & 3) * 2 - 3;
    y_check = (reg_b & 12) == 0 ?  0 : (reg_b & 12) / 2 - 3;
    z_check = (reg_b & 48) == 0 ? -1 : (reg_b & 48) / 16 - 1;

    if (x_check)
    { 
      param = (x_check - b->x) / (a->x - b->x);
      if (max_param < param)
      {
        max_param = param;
        min = 0;
      }
    }
    if (y_check)
    { 
      param = (y_check - b->y) / (a->y - b->y);
      if (max_param < param)
      {
        max_param = param;
        min = 1; 
      }
    }
    
    if (z_check + 1)
    { 
      param = (z_check - b->z) / (a->z - b->z); 
      if (max_param < param)
      { 
        max_param = param;
        min = 2; 
      }
    }
    
    if (min == 0) 
    { 
      if(b->x < x_check)
      {
        if(x_check == 1) b->x=1+.000001; b->x=-1; 
      }
      if  (b->x > x_check) 
      { 
        if (x_check == -1) b->x=-1-.000001; b->x=1; 
      }
    }
    else 
    {
      b->x = max_param * (a->x - b->x) + b->x;
    }
    
    if (min == 1) 
    {
      if (b->y < y_check)
      { 
        if (y_check == 1) b->y=1+.000001; b->y=-1; 
      }
      if (b->y > y_check)
      { 
        if (y_check==-1) b->y=-1-.000001; b->y=1; 
      }
    }
    else
    {
      b->y = max_param * (a->y - b->y) + b->y;
    }
    if (min == 2) 
    {
      if (b->z < z_check)
      {
        if (z_check == 1) b->z = 1 + .000001; b->z = 0; 
      } 
      if (b->z > z_check)
      {
        if (z_check == 0) b->z = 0 - .000001; b->z = 1; 
      }
    }
    else
    {
      b->z = max_param * (a->z-b->z) + b->z;
    }
    if(!testValid(*b)) 
    {
      return 0;
    }
    ret=2;
  }
  return ret;
}

void scanConvert(Vertex a, Vertex b)
{
  int tx1 = ((a.x + 1) * (MAX_W -1 )) / 2; 
  int tx2 = ((b.x + 1) * (MAX_W - 1)) / 2; 
  int ty1 = ((a.y + 1) * (MAX_H - 1)) / 2;
  int ty2 = ((b.y + 1) * (MAX_H - 1)) / 2;

  int x1, x2, y1, y2;
  int dx, dy, err=0, incr;
  float m = (tx2 == tx1) ? 100 : (float) (ty2 - ty1) / (float) (tx2 - tx1), 
  float tz1 = a.z, tz2 = b.z, z1, z2, dz;

  if(m >1 || m < -1)
  {
    if(ty1 < ty2)
    { 
      y1 = ty1; 
      y2 = ty2;
      x1 = tx1;
      x2 = tx2;
      z1 = tz1;
      z2 = tz2;
    }
    else
    {
      y1 = ty2;
      y2 = ty1;
      x1 = tx2;
      x2 = tx1;
      z1 = tz2;
      z2 = tz1;
    }
  } 
  else 
  {
    if(tx1 < tx2)
    { 
      x1 = tx1;
      x2 = tx2;
      y1 = ty1;
      y2 = ty2; 
      z1 = tz1;
      z2 = tz2; 
    }
    else
    { 
      x1 = tx2;
      x2 = tx1;
      y1 = ty2;
      y2 = ty1;
      z1 = tz2;
      z2 = tz1;
    }
  }
  
  if (x1 == 0)
  {
    if (y0min == -1)
    { 
      y0min = y1;
      y0max = y1;
    }
    else
    { 
      y0min = (y1 < y0min) ? y1 : y0min;
      y0max = (y1 > y0max) ? y1 : y0max; 
    } 
  }
  
  if (x2 == 0)
  { 
    if (y0min == -1)
    {
      y0min = y2;
      y0max = y2;
    }
    else
    { 
      y0min = (y2 < y0min) ? y2 : y0min;
      y0max = (y2 > y0max) ? y2 : y0max; 
    }
  }
  
  if (x1 == MAX_W - 1)
  {
    if (y1min == -1)
    {
      y1min = x1;
      y1max = x1;
    }
    else
    { 
      y1min = (y1 < y1min) ? y1 : y1min; 
      y1max = (y1 > y1max) ? y1 : y1max;
    }
  }
  
  if (x2 == MAX_W - 1)
  {
    if (y1min == -1)
    {
      y1min = x2;
      y1max = x2;
    }
    else
    { 
      y1min = (y2 < y1min) ? y2 : y1min; 
      y1max = (y2 > y1max) ? y2 : y1max;
    }
  }
  
  dx = abs (x2 - x1);
  dy = abs (y2 - y1);
  err = 0;
  //printf("%d %d %f, %d %d %f, %d, %d\n", x1, y1, z1, x2, y2, z2, dx, dy);
  
  if (m <= 1 && m >= -1)
  {
    incr = m > 0 ? 1 : -1;
    dz = (z2 - z1) / dx;
    
    for( ; x1 <= x2; ++x1)
    {
      addToPointsTable(x1, y1, z1);
      if( 2 * (err + dy) < dx)
      {
        err = err + dy;
      }
      else 
      { 
        y1 += incr; 
        err = err + dy - dx; 
      }
      z1 += dz;
    }
  } 
  else 
  {
    incr = m > 0 ? 1 : -1;
    dz = (z2 - z1) / dy;
    for( ; y1 <= y2; ++y1)
    {
      addToPointsTable(x1, y1, z1);
      if(2 * (err + dx) < dy) 
      {
        err=err+dx;
      }
      else
      {
        x1 += incr;
        err = err + dx - dy; 
      }
      z1 += dz;
    }
  }
  
}

void fillTriangle(Colour colour)
{
  int i, j, no_pix=0;
  float z, dz;
  if(y0min>=0){
    z=pointsTable[y0min][1];
    dz=(float)(pointsTable[y0min][3]-pointsTable[y0min][1])/(float)(pointsTable[y0min][2]-pointsTable[y0min][0]);
    for(i=y0min; i<=y0max; ++i){
      addToPointsTable(0, i, z);
      z+=dz;
    }
  }
  if(y1min>=0){
    z=pointsTable[y1min][1];
    dz=(float)(pointsTable[y1min][3]-pointsTable[y1min][1])/(float)(pointsTable[y1min][2]-pointsTable[y1min][0]);
    for(i=y1min; i<=y1max; ++i){
      addToPointsTable(MAX_W-1, i, z);
      z+=dz;
    }
  }
  for(i=0;i<MAX_H;i++){
    if(pointsTable[i][0]>=0){
      dz=(pointsTable[i][3]-pointsTable[i][1])/(pointsTable[i][2]-pointsTable[i][0]);
      z=pointsTable[i][1];
      for(j=pointsTable[i][0]; j<=pointsTable[i][2]; ++j){
        if(zBuffer[MAX_W*j+i]>z){
          zBuffer[MAX_W*j+i]=z;
          data[MAX_W*j+i]=colour;
          ++no_pix;
        }
        z+=dz;
      }
    }
  }
  if(DBG) printf("No_pix: %d\n", no_pix);
}

void drawTriangle(Triangle t)
{
  Vertex l1v1=t.v1, l1v2=t.v2, l2v1=t.v2, l2v2=t.v3, l3v1=t.v3, l3v2=t.v1;
  int i, cuta, cutb, cutc;
  if(!pointsTable) pointsTable = malloc(4*MAX_H*sizeof(float));
  y0min=-1; y0max=-1; y1min=-1; y1max=-1;
  for(i=0;i<MAX_H;++i){ pointsTable[i][0]=-1; pointsTable[i][2]=-1; }
  cuta=clip(&l1v1, &l1v2);
  if(cuta==2 || !cuta)
      if(DBG) printf("Clipped (%d): %f %f %f, %f %f %f => %f %f %f, %f %f %f\n", cuta, t.v1.x, t.v1.y, t.v1.z, t.v2.x, t.v2.y, t.v2.z, l1v1.x, l1v1.y, l1v1.z, l1v2.x, l1v2.y, l1v2.z);
  if(cuta)
      scanConvert(l1v1, l1v2);
  cutb=clip(&l2v1, &l1v2);
  if(cutb==2 || !cutb)
      if(DBG) printf("Clipped (%d): %f %f %f, %f %f %f => %f %f %f, %f %f %f\n", cutb, t.v1.x, t.v1.y, t.v1.z, t.v2.x, t.v2.y, t.v2.z, l2v1.x, l2v1.y, l2v1.z, l2v2.x, l2v2.y, l2v2.z);
  if(cutb)
    scanConvert(l2v1, l2v2);
  cutc=clip(&l3v1, &l3v2);
  if(cutc==2 || !cutc)
     if(DBG) printf("Clipped (%d): %f %f %f, %f %f %f => %f %f %f, %f %f %f\n", cutc, t.v1.x, t.v1.y, t.v1.z, t.v1.x, t.v1.y, t.v1.z, l3v1.x, l3v1.y, l3v1.z, l3v2.x, l3v2.y, l3v2.z);
  if(cutc)
    scanConvert(l3v1, l3v2);
//  glDrawPixels(MAX_W, MAX_H, GL_RGBA, GL_BYTE, data);
//  glFlush();
//  glDrawPixels(MAX_W, MAX_H, GL_RGBA, GL_BYTE, data);
//  glFlush();
  fillTriangle(t.colour);
//  glDrawPixels(MAX_W, MAX_H, GL_RGBA, GL_BYTE, data);
//  glFlush();
}

void printPointsTable()
{
  int i;
  for(i = 0; i < MAX_H; ++i)
  {
    if (pointsTable[i][0] >= 0)
    {
      if(DBG) 
        printf("%d: %f %f\n", i, pointsTable[i][0], pointsTable[i][2]);
    }
  }
}

//Look at the rectangle from opposite its normal. Choose the top left and top right vertices.
void addRectangle(Vertex a, Vertex b, Colour colour)
{
  addTriangle(triangle(a, b, vertex(-a.x, -a.y, -a.z), colour));
  addTriangle(triangle(a, vertex(-a.x, -a.y, -a.z), vertex(-b.x, -b.y, -b.z), colour));
}

void initScene()
{
  clearAllTriangles();
}

void renderScene()
{
  initDraw();
  transformTriangles();
  drawTriangles();
}

void setViewer (Vertex eye, Vertex lookAt, Vertex up)
{
  Vertex f = subVertex (lookAt, eye), s, u;
  float matrix[16];
  MatrixMode mode = getMatrixMode();

  f = normalizeVertex(f);
  up = normalizeVertex(up);
  s = crossProduct(f,up);
  u = crossProduct(s,f);

  // Set matrix elements.
  matrix[index (0,0)] = s.x; 
  matrix[index (0,1)] = u.x;
  matrix[index (0,2)] = f.x;
  matrix[index (0,3)] = 0;
  matrix[index (1,0)] = s.y;
  matrix[index (1,1)] = u.y;
  matrix[index (1,2)] = f.y;
  matrix[index (1,3)] = 0;
  matrix[index (2,0)] = s.z;
  matrix[index (2,1)] = u.z;
  matrix[index (2,2)] = f.z; 
  matrix[index (2,3)] =0;
  matrix[index (3,0)] = -dotProduct (eye, s); 
  matrix[index (3,1)] = -dotProduct (eye, u); 
  matrix[index (3,2)] = -dotProduct (eye, f); 
  matrix[index (3,3)] = 1;

  setMatrixMode(PROJECTION);
  multMatrix(matrix);
  setMatrixMode(mode);
}

void setFrustum(float width, float height, float near, float far)
{
  float matrix[16];
  int i = getMatrixMode();
 
  // Set all elements to zero.
  memset (matrix, 0, SIZEOF_MATRIX);

  // Set particular elements.
  matrix[index (0,0)] = 2 * near / width; 
  matrix[index (1,1)] = 2 * near / height;
  matrix[index (2,2)] = far / (far - near);
  matrix[index (2,3)] = 1;
  matrix[index (3,2)] = - near * far / (far - near);
 
  // Set matrix mode to Projection.
  setMatrixMode(PROJECTION);

  // Multiply matrix.
  multMatrix(matrix);

  // Reset matrix mode back to initial value.
  setMatrixMode(i);
}

