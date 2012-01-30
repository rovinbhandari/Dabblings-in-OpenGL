#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

float angle=0.0,deltaAngle = 0.0,ratio;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int font=(int)GLUT_BITMAP_8_BY_13;
static GLint snowman_display_list;
int bitmapHeight=13;

int frame,time,timebase=0;
char s[30];

void initWindow();

void changeSize(int w1, int h1)
    {    
    if(h1 == 0)
        h1 = 1;

    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
        gluPerspective(45,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 
              x + lx,y + ly,z + lz,
              0.0f,1.0f,0.0f);
    }

void drawSnowMan() {

    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);

    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);

    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
}

GLuint createDL() {
    GLuint snowManDL;
    
    snowManDL = glGenLists(2);

    glNewList(snowManDL+1,GL_COMPILE);
        drawSnowMan();
    glEndList();

    glNewList(snowManDL,GL_COMPILE);

    int i, j;
    for(i = -3; i < 3; i++)
        for(j=-3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i*10.0,0,j * 10.0);
            glCallList(snowManDL+1);
            glPopMatrix();
        }

    glEndList();

    return(snowManDL);
}

void initScene() {

    glEnable(GL_DEPTH_TEST);
    snowman_display_list = createDL();

}

void orientMe(float ang) {

    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z, 
              x + lx,y + ly,z + lz,
              0.0f,1.0f,0.0f);
}

void moveMeFlat(int i) {
    x = x + i*(lx)*0.1;
    z = z + i*(lz)*0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, 
              x + lx,y + ly,z + lz,
              0.0f,1.0f,0.0f);
}

void setOrthographicProjection() {
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
       gluOrtho2D(0, w, 0, h);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font,char *string)
{  
  char *c;
  
  glRasterPos2f(x, y);
  
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void renderScene(void) {

    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Draw ground

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

// Draw 36 SnowMen

    glCallList(snowman_display_list);
    
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
        timebase = time;        
        frame = 0;
    }

    glColor3f(0.0f,1.0f,1.0f);
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    renderBitmapString(30,15,(void *)font,"GLUT Tutorial @ 3D Tech"); 
    renderBitmapString(30,35,(void *)font,s);
    renderBitmapString(30,55,(void *)font,"Esc - Quit");
    glPopMatrix();
    resetPerspectiveProjection();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 27) 

        exit(0);
    
    }

void pressKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
        case GLUT_KEY_UP : deltaMove = 1;break;
        case GLUT_KEY_DOWN : deltaMove = -1;break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT : if (deltaAngle < 0.0f) 
                                 deltaAngle = 0.0f;
                             break;
        case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f) 
                                 deltaAngle = 0.0f;
                             break;
        case GLUT_KEY_UP :     if (deltaMove > 0) 
                                 deltaMove = 0;
                             break;
        case GLUT_KEY_DOWN : if (deltaMove < 0) 
                                 deltaMove = 0;
                             break;
    }
}

void initWindow() {
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    initScene();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,360);
    glutCreateWindow("SnowMen from Lighthouse3D");

    // register all callbacks
    initWindow();

    glutMainLoop();

    return(0);
}


