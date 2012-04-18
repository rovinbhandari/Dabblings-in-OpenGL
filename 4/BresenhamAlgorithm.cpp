#include <BresenhamAlgorithm.hpp>

#define TOLERANCE 0.00001
static bool CompareDoubles(double a, double b)
{
	if(fabs(a - b) <= fabs(a) * TOLERANCE
	   || fabs(a - b) <= fabs(b) * TOLERANCE)
		return true;
	return false;
}

#define INTERVAL1 0.01
#define INTERVAL2 0.0001

// m<-1, m=-1 -1<m<0 0<m<1,m=1,m>1,dx=0,dy=0
/* Bresenham line-drawing procedure */
void BresenhamLine(Pt2D a, Pt2D b, Color c)
{	
	double dx = b.x - a.x;  
	double dy = b.y - a.y;
	Pt2D t(0.0, 0.0);
	glColor3f (c.r, c.g, c.b);
	glBegin(GL_POINTS);
	if(CompareDoubles(dx, 0))
	{
		if(a.y > b.y)
		{
			t.y = b.y;
			b.y = a.y;
		}
		else 
			t.y = a.y;
		while(t.y <= b.y)
		{
			glVertex2f(a.x, t.y);
			t.y += INTERVAL1;
		}
	}
	else if(CompareDoubles(dy, 0))
	 {
		if(a.x > b.x)
		{
			t.x = b.x;
			b.x = a.x;
		}
		else 
			t.x = a.x;
		while(t.x <= b.x)
		{
			glVertex2f(t.x, a.y);
			t.x += INTERVAL1;
		}
	 }
	 // |slope| < 1 
	 else if(fabs(dy) < fabs(dx))
	  { //printf("slope < 1 \n");
		double p = 2*(fabs(dy)) - (fabs(dy));
		double twoDy = 2*fabs(dy), twoDyMinusDx = 2*(fabs(dy)-fabs(dx));

		// Determine which endpoint to use as start position.
		if(a.x > b.x) {
			t.x = b.x;
			t.y = b.y;
			b.x = a.x; 
		}
		else 
		{
			t.x = a.x;
			t.y = a.y;
		}
		glVertex2f(t.x, t.y);
//printf("slope < 1 \n");
		while(t.x < b.x)
		{
			t.x += INTERVAL2;
			if(p < 0)
				p += twoDy;
			else  
			{
				if (dx * dy > 0)
					t.y += INTERVAL1;	// slope > 0
				else 
					t.y -= INTERVAL1;	// slope < 0
				p += twoDyMinusDx;
			}	
			glVertex2f(t.x, t.y);
		}
	  }
	  // |slope| > 1
	  else if (fabs(dy) > fabs(dx))  
	  {//printf("slope > 1 \n");
		double p = 2*(fabs(dx)) - (fabs(dy));
		double twoDx = 2*fabs(dx), twoDxMinusDy = 2*(fabs(dx)-fabs(dy));
		// Determine which endpoint to use as start position.
		if (a.y > b.y) {
			t.y = b.y;
			t.x = b.x;
			b.y = a.y; 
		}
		else {
			t.x = a.x;
			t.y = a.y;
		}
		glVertex2f(t.x, t.y);

		while(t.y < b.y)
		{
			t.y += INTERVAL2;
			{
			
				if(p < 0)
					p += twoDx;
				else 
				{
					if (dx * dy > 0)
						t.x += INTERVAL1;
					else  
						t.x -= INTERVAL1;
					p += twoDxMinusDy;
				}	
			}
			glVertex2f(t.x, t.y);
		}
	  }
	  // |slope|= 1
	  else if(CompareDoubles(fabs(dx), fabs(dy)))
	  {//printf("slope = 1 \n");
		if (a.x > b.x) 
		{
		   t.x = b.x;
		   t.y = b.y;
		   b.x = a.x; 
		}
		else 
		{
		   t.x = a.x;
		   t.y = a.y;
		}
		glVertex2f(t.x, t.y);
		while(t.x < b.x)
		{
		  t.x += INTERVAL2;
          	  if(CompareDoubles(dx, dy))
			t.y += INTERVAL1;
	  	  else
			t.y -= INTERVAL1;
	  	  glVertex2f(t.x, t.y);
		}
	  }
	  glEnd();
}
