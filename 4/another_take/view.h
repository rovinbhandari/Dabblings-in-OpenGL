void setViewer(Vertex eye, Vertex lookAt, Vertex up){
  Vertex f = subVertex(lookAt, eye), s, u;
  float m[16];
  int i=getMatrixMode();
  f=normalizeVertex(f);
  up=normalizeVertex(up);
  s=crossProduct(f,up);
  u=crossProduct(s,f);
  m[0]=s.x; m[1]=u.x; m[2]=f.x; m[3]=0;
  m[4]=s.y; m[5]=u.y; m[6]=f.y; m[7]=0;
  m[8]=s.z; m[9]=u.z; m[10]=f.z; m[11]=0;
  m[12]=-dotProduct(eye, s); m[13]=-dotProduct(eye, u); m[14]=-dotProduct(eye, f); m[15]=1;
  setMatrixMode(PROJECTION);
  multMatrix(m);
  setMatrixMode(i);
}

void setFrustum(float w, float h, float n, float f){
  float m[16];
  int i=getMatrixMode();
  m[0]=2*n/w; m[1]=0; m[2]=0; m[3]=0;
  m[4]=0; m[5]=2*n/h; m[6]=0; m[7]=0;
  m[8]=0; m[9]=0; m[10]=f/(f-n); m[11]=1;
  m[12]=0; m[13]=0; m[14]=-n*f/(f-n); m[15]=0;
  setMatrixMode(PROJECTION);
  multMatrix(m);
  setMatrixMode(i);
}
