#include<graphics.h>
#include<stdlib.h>
#include<iostream.h>
#include<conio.h>

void putellipsepixels(int xc, int yc, int x, int y)
{
	putpixel(xc + x, yc + y, GREEN);
	putpixel(xc + x, yc - y, GREEN);
	putpixel(xc - x, yc + y, GREEN);
	putpixel(xc - x, yc - y, GREEN);
}

void midpointellipse(int xc, int yc, long rx, long ry)
{
	int x = 0, y = ry;
	// Region 1
	float p1 = ry*ry - rx*rx*ry + rx*rx/4;
	while (2.0*ry*ry*x <= 2.0*rx*rx*y)
	{
		putellipsepixels(xc,yc,x,y);
		x++;
		if (p1 < 0)
		{
			p1 = p1 + 2*ry*ry*x + ry*ry;
		}
		else
		{
			y--;
			p1 = p1 + 2*ry*ry*x - 2*rx*rx*y - ry*ry;
		}
	}

	// Region 2
	float p2 = ry*ry*(x+0.5)*(x+0.5) + rx*rx*(y-1)*(y-1) - rx*rx*ry*ry;
	while(y >= 0)
	{
		putellipsepixels(xc,yc,x,y);
		y--;
		if (p2 <= 0)
		{
			x++;
			p2 = p2 + 2*ry*ry*x - 2*rx*rx*y + rx*rx;
		}
		else
		{
			p2 = p2 - 2*rx*rx*y + rx*rx;
		}
	}
}

void main()
{
	clrscr();
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
	int xc, yc;
	long rx,ry;
	cout<<"Enter the coordinates of centre ==>> ";
	cin>>xc>>yc;
	cout<<"Enter radii (rx, ry) of ellipse ==>> ";
	cin>>rx>>ry;
	midpointellipse(xc,yc,rx,ry);
	getch();
	closegraph();
}