typedef struct _Polygon{
  Vertex *v;
  struct _Polygon *nextVertex;
}Polygon;

typedef struct _PolygonList{
  Polygon *vertices;
  unsigned int colour;
  struct _PolygonList *next;
}Polygonlist;

PolygonList *global;
int polygonInProgress=0;
Polygon *polygonVertices;

void createPolygon(){
  polygonInProgress=1;
  current = (Polygon *)malloc(sizeof(Polygon));
  current->v=NULL;
  current->nextVertex=NULL;
  if(!global){
    global = (PolygonList *)malloc(sizeof(PolygonList));
    global->vertices=current;
    global->next=NULL;
  } else {
    global->next=current;
  }
}

void addVertex(Vertex *v){
  Polygon newVertex=(Polygon *)malloc(sizeof(Polygon));
  newVertex->v=v;
  newVertex->next=NULL;
  current->next=newVertex;
}
