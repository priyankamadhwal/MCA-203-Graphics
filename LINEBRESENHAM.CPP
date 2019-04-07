#include<iostream.h>
#include<graphics.h>
#include<conio.h>

void bresenham(int xa, int ya, int xb, int yb)
{
	int dx, dy, p, x, y;
	x = xa;
	y = ya;
	dx = xb - xa;
	dy = yb - ya;
	p = 2 * dy - dx;
	while (x < xb)
	{
		putpixel(x,y,GREEN);
		if (p < 0)
		{
			p = p + 2*dy ;
		}
		else
		{
			y += 1;
			p = p + 2*dy - 2*dx;
		}
		x += 1;
	}
}

void main()
{
	clrscr();
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
	int xa, ya, xb, yb;
	cout<<"Enter the leftmost coordinate ==>> ";
	cin>>xa>>ya;
	cout<<"Enter the rightmost coordinate ==>> ";
	cin>>xb>>yb;
	bresenham(xa, ya, xb, yb);
	getch();
	closegraph();
}