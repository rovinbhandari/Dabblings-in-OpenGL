/*
 *  cube.c
 *  This program demonstrates a single modeling transformation,
 *  glScalef() and a single viewing transformation, gluLookAt().
 *  A wireframe cube is rendered.
 */
#include <GL/glui.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float v[3][8], normal[3][8], ls[] = {10,10,10}, ve[] = {7,7,7}, I[8], ka = 1.0, kd = 1.0, ks = 1.0, ia = 0.2, il = 1.0, ns = 10, side = 10.0, zNear = 5.0, zFar = 25.0;
int main_window, j = 0, angle = 45;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   //glShadeModel (GL_FLAT);
}

void perspective_proj(int fovy, float aspect, float znear, float zfar)
{
    float A, B, C, D, f, theta;
    if(znear < zfar)
    {
	    theta = (180/3.14) * fovy; 
	    f = 1/tanf(theta/2);
	    A = f/aspect;
	    B = f;
	    C = (zfar + znear)/(znear-zfar);
	    D = (2*zfar*znear)/(znear-zfar);

	    GLfloat m[] = { A, 0, 0, 0,
		            0, B, 0, 0,
		            0, 0, C, D,
		            0, 0, -1, 0
		          };
	     glMultTransposeMatrixf(m);
    }
}

void crossproduct(float normal1[3], float normal2[3], float normal3[])
{
	normal3[0] = normal1[1]*normal2[2] - normal1[2]*normal2[1];
	normal3[1] = normal2[0]*normal1[2] - normal1[0]*normal2[2];
	normal3[2] = normal1[0]*normal2[1] - normal2[0]*normal1[1];
}

void calcnormalatvref(float vref[3], float va[3], float vb[3], float vc[3], int a)
{
	float temp[3], normal1[3], normal2[3], normal3[3], normal4[3], normal5[3], normal6[3];
	int i;
	for(i =0; i < 3; i++)
	{
		normal1[i] = va[i] - vref[i] ;
		normal2[i] = vb[i] - vref[i] ;
		normal3[i] = vc[i] - vref[i] ;
	}

	crossproduct(normal1,normal2,normal4);
	crossproduct(normal2,normal3,normal5);
	crossproduct(normal3,normal1,normal6);

	temp[0] = sqrt(pow(normal4[0],2) + pow(normal4[1],2) + pow(normal4[2],2));
	temp[1] = sqrt(pow(normal5[0],2) + pow(normal5[1],2) + pow(normal5[2],2));
	temp[2] = sqrt(pow(normal6[0],2) + pow(normal6[1],2) + pow(normal6[2],2));

	normal[0][a] = (normal4[0]/temp[0] + normal5[0]/temp[1] + normal6[0]/temp[2]);
	normal[1][a] = (normal4[1]/temp[0] + normal5[1]/temp[1] + normal6[1]/temp[2]);
	normal[2][a] = (normal4[2]/temp[0] + normal5[2]/temp[1] + normal6[2]/temp[2]);
	
	float var = 0.0;
	var = sqrt(pow(normal[0][a],2) + pow(normal[1][a],2) + pow(normal[2][a],2));

	for(i = 0; i < 3; i++)
		normal[i][a] /= var;
}

void calcnormal(float vertex[3][8])
{
	float a[3], b[3], c[3], d[3];
	int i;

	//at v0
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][0];
		b[i] = vertex[i][4];
		c[i] = vertex[i][3];
		d[i] = vertex[i][1];
	}
	calcnormalatvref(a,b,c,d,0);

	//at v1
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][1];
		b[i] = vertex[i][5];
		c[i] = vertex[i][2];
		d[i] = vertex[i][0];
	}
	calcnormalatvref(a,d,c,b,1);

	//at v2
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][2];
		b[i] = vertex[i][6];
		c[i] = vertex[i][3];
		d[i] = vertex[i][1];
	}
	calcnormalatvref(a,d,c,b,2);

	//at v3
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][3];
		b[i] = vertex[i][7];
		c[i] = vertex[i][2];
		d[i] = vertex[i][0];
	}
	calcnormalatvref(a,b,c,d,3);

	//at v4
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][4];
		b[i] = vertex[i][7];
		c[i] = vertex[i][5];
		d[i] = vertex[i][0];
	}
	calcnormalatvref(a,d,c,b,4);

	//at v5
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][5];
		b[i] = vertex[i][6];
		c[i] = vertex[i][4];
		d[i] = vertex[i][1];
	}
	calcnormalatvref(a,b,c,d,5);

	//at v6
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][6];
		b[i] = vertex[i][7];
		c[i] = vertex[i][5];
		d[i] = vertex[i][2];
	}
	calcnormalatvref(a,b,c,d,6);

	//at v7
	for(i = 0; i < 3; i++)	
	{
		a[i] = vertex[i][7];
		b[i] = vertex[i][6];
		c[i] = vertex[i][4];
		d[i] = vertex[i][3];
	}
	calcnormalatvref(a,d,c,b,7);
}

void calcintensityatvref(float vref[3], int a)
{
	float temp1[3], temp2[3], temp3[3], temp4, temp5, temp6, lv[3], vv[3], r[3], dp1, dp2;
	int i;

	for(i = 0; i < 3; i++)
	{
		temp1[i] = ls[i] - vref[i];
		temp2[i] = ve[i] - vref[i];
	}

	temp4 = sqrt(pow(temp1[0],2) + pow(temp1[1],2) + pow(temp1[2],2));
	temp5 = sqrt(pow(temp2[0],2) + pow(temp2[1],2) + pow(temp2[2],2));
	
	for(i = 0; i < 3; i++)
	{
		lv[i] = temp1[i]/temp4;	
		vv[i] = temp2[i]/temp5;
	}

	dp1 = normal[0][a]*lv[0] + normal[1][a]*lv[1] + normal[2][a]*lv[2]; 

	if(dp1 >= 0.0)
	{
		for(i = 0; i < 3; i++)
		{
			temp3[i] = 2*dp1*normal[i][a] - lv[i];
		}

		temp6 = sqrt(pow(temp3[0],2) + pow(temp3[1],2) + pow(temp3[2],2));

		for(i = 0; i < 3; i++)
			r[i] = temp3[i]/temp6;	

		dp2 = vv[0]*r[0] + vv[1]*r[1] + vv[2]*r[2];
	}
	else
	{
		dp1 = dp2 = 0.0;
	}
	if(dp2 < 0.0)
		dp2 = 0.0;
	
	I[a] = ka*ia + il*(kd*dp1 + ks*pow(dp2,ns));
}

void drawcube(float side)
{
	float edge = side/2;
	
	v[0][1] = v[0][2] = v[0][5] = v[0][6] = edge;
	v[0][0] = v[0][3] = v[0][4] = v[0][7] = (-1) * edge;
	v[1][1] = v[1][2] = v[1][3] = v[1][0] = (-1) * edge;
	v[1][5] = v[1][6] = v[1][7] = v[1][4] = edge;
	v[2][1] = v[2][5] = v[2][4] = v[2][0] = edge;
	v[2][3] = v[2][2] = v[2][6] = v[2][7] = (-1) * edge; 

//solidcube
	glBegin(GL_QUADS);	// Start Drawing The Cube

	glColor3f( 1.0f, 0.0f, 0.0f);
	glVertex3f( v[0][6], v[1][6], v[2][6]);		// Top Right Of The Quad (Top)
	glVertex3f( v[0][7], v[1][7], v[2][7]);		// Top Left Of The Quad (Top)
	glVertex3f( v[0][4], v[1][4], v[2][4]);		// Bottom Left Of The Quad (Top)
	glVertex3f( v[0][5], v[1][5], v[2][5]);		// Bottom Right Of The Quad (Top)

	glColor3f( 0.0f, 1.0f, 0.0f);
	glVertex3f( v[0][2], v[1][2], v[2][2]);		// Top Right Of The Quad (Bottom)
	glVertex3f( v[0][3], v[1][3], v[2][3]);		// Top Left Of The Quad (Bottom)
	glVertex3f( v[0][0], v[1][0], v[2][0]);		// Bottom Left Of The Quad (Bottom)
	glVertex3f( v[0][1], v[1][1], v[2][1]);		// Bottom Right Of The Quad (Bottom)

	glColor3f( 0.0f, 0.0f, 1.0f);
	glVertex3f( v[0][5], v[1][5], v[2][5]);		// Top Right Of The Quad (Front)
	glVertex3f( v[0][4], v[1][4], v[2][4]);		// Top Left Of The Quad (Front)
	glVertex3f( v[0][0], v[1][0], v[2][0]);		// Bottom Left Of The Quad (Front)
	glVertex3f( v[0][1], v[1][1], v[2][1]);		// Bottom Right Of The Quad (Front)

	glColor3f( 1.0f, 1.0f, 0.0f);
	glVertex3f( v[0][6], v[1][6], v[2][6]);		// Bottom Left Of The Quad (Back)
	glVertex3f( v[0][7], v[1][7], v[2][7]);		// Bottom Right Of The Quad (Back)
	glVertex3f( v[0][3], v[1][3], v[2][3]);		// Top Right Of The Quad (Back)
	glVertex3f( v[0][2], v[1][2], v[2][2]);		// Top Left Of The Quad (Back)

	glColor3f( 1.0f, 0.0f, 1.0f);
	glVertex3f( v[0][7], v[1][7], v[2][7]);		// Top Right Of The Quad (Left)
	glVertex3f( v[0][4], v[1][4], v[2][4]);		// Top Left Of The Quad (Left)
	glVertex3f( v[0][0], v[1][0], v[2][0]);		// Bottom Left Of The Quad (Left)
	glVertex3f( v[0][3], v[1][3], v[2][3]);		// Bottom Right Of The Quad (Left)

	glColor3f( 0.0f, 1.0f, 1.0f);
	glVertex3f( v[0][6], v[1][6], v[2][6]);		// Top Right Of The Quad (Right)
	glVertex3f( v[0][5], v[1][5], v[2][5]);		// Top Left Of The Quad (Right)
	glVertex3f( v[0][1], v[1][1], v[2][1]);		// Bottom Left Of The Quad (Right)
	glVertex3f( v[0][2], v[1][2], v[2][2]);		// Bottom Right Of The Quad (Right)

	glEnd();

//wirecube
	/*glBegin(GL_LINE);	// Start Drawing The Cube

	glVertex3f( v[0][6], v[1][6], v[2][6]);		
	glVertex3f( v[0][7], v[1][7], v[2][7]);		//line b/w v7 and v6
	glVertex3f( v[0][7], v[1][7], v[2][7]);		
	glVertex3f( v[0][3], v[1][3], v[2][3]);		//line b/w v7 and v3
	glVertex3f( v[0][7], v[1][7], v[2][7]);		
	glVertex3f( v[0][4], v[1][4], v[2][4]);		//line b/w v7 and v4

	glVertex3f( v[0][6], v[1][6], v[2][6]);		
	glVertex3f( v[0][5], v[1][5], v[2][5]);		//line b/w v6 and v5
	glVertex3f( v[0][6], v[1][6], v[2][6]);	
	glVertex3f( v[0][2], v[1][2], v[2][2]);		//line b/w v6 and v2

	glVertex3f( v[0][1], v[1][1], v[2][1]);		
	glVertex3f( v[0][5], v[1][5], v[2][5]);		//line b/w v5 and v1
	glVertex3f( v[0][4], v[1][4], v[2][4]);		
	glVertex3f( v[0][5], v[1][5], v[2][5]);		//line b/w v5 and v4

	glVertex3f( v[0][4], v[1][4], v[2][4]);		
	glVertex3f( v[0][0], v[1][0], v[2][0]);		//line b/w v4 and v0

	glVertex3f( v[0][3], v[1][3], v[2][3]);		
	glVertex3f( v[0][0], v[1][0], v[2][0]);		//line b/w v3 and v0
	glVertex3f( v[0][3], v[1][3], v[2][3]);		
	glVertex3f( v[0][2], v[1][2], v[2][2]);		//line b/w v3 and v2

	glVertex3f( v[0][1], v[1][1], v[2][1]);		
	glVertex3f( v[0][2], v[1][2], v[2][2]);		//line b/w v1 and v2

	glVertex3f( v[0][0], v[1][0], v[2][0]);
	glVertex3f( v[0][1], v[1][1], v[2][1]);		//line b/w v1 and v0

	glEnd();*/
}

void printintensity(float vertex[3][8])
{
	int i;
	float vref[3];
	calcnormal(vertex);
	FILE *fp;
	fp = fopen("output.txt","a");
	fprintf(fp, "Reading No.: %d\n", j);
	for(i = 0; i < 8; i++)
	{	
		vref[0] = vertex[0][i];
		vref[1] = vertex[1][i];
		vref[2] = vertex[2][i];
		calcintensityatvref(vref,i);
		fprintf(fp, "Intensity at vertex(%f,%f,%f) : %f\n", vref[0], vref[1], vref[2], I[i]);
	}
	j++;
	fclose(fp);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (ve[0], ve[1], ve[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
   //glutWireCube (1.0);
	drawcube(side);
	printintensity(v);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   perspective_proj(angle, 1.0, zNear, zFar);
   //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (100, 100);
   main_window = glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
//New Addition
		glEnable(GL_DEPTH_TEST);
		GLUI *glui = GLUI_Master.create_glui( "GLUI" );
		glui = GLUI_Master.create_glui_subwindow( main_window,GLUI_SUBWINDOW_RIGHT );

		GLUI_Rollout *sidelength = new GLUI_Rollout(glui, "Sidelength", true );
		(new GLUI_Spinner( sidelength, "value:", &side ))
		    ->set_float_limits( 0.0, 50.0 );

		GLUI_Rollout *viewer = new GLUI_Rollout(glui, "Viewers Eye", true);
		(new GLUI_Spinner( viewer, "X Co-ordinate:", &ve[0] ))
		    ->set_float_limits( -100.0, 100.0 );
		(new GLUI_Spinner( viewer, "Y Co-ordinate:", &ve[1] ))
		    ->set_float_limits( -100.0, 100.0 );
		(new GLUI_Spinner( viewer, "Z Co-ordinate:", &ve[2] ))
		    ->set_float_limits( -100.0, 100.0 );

		GLUI_Rollout *light = new GLUI_Rollout(glui, "Light Source", true );
		(new GLUI_Spinner( light, "X Co-ordinate:", &ls[0] ))
		    ->set_float_limits( -100.0, 100.0 );
		(new GLUI_Spinner( light, "Y Co-ordinate:", &ls[1] ))
		    ->set_float_limits( -100.0, 100.0 );
		(new GLUI_Spinner( light, "Z Co-ordinate:", &ls[2] ))
		    ->set_float_limits( -100.0, 100.0 );

		/*GLUI_Rollout *proj = new GLUI_Rollout(glui, "Projection", true );
		(new GLUI_Spinner( proj, "Angle:", &angle ))
		    ->set_int_limits( 0, 360 );
		(new GLUI_Spinner( proj, "Near Z Co-ordinate:", &zNear ))
		    ->set_float_limits( -100.0, 100.0 );
		(new GLUI_Spinner( proj, "Far Z Co-ordinate:", &zFar ))
		    ->set_float_limits( -100.0, 100.0 );*/
   
		new GLUI_Button(glui, "Quit", 0,(GLUI_Update_CB)exit );

		glui->set_main_gfx_window( main_window );
//Addition ends here*/
   glutMainLoop();
   return 0;
}
