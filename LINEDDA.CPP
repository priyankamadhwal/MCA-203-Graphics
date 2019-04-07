#include<iostream.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>

void DDA(int xa, int ya, int xb, int yb)
{
	int dx, dy, steps, x, y;
	float xInc, yInc;
	x = xa;
	y = ya;
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xInc = dx / float(steps);
	yInc = dy / float(steps);
	putpixel(x,y,GREEN);
	for (int k=0; k<steps; k++)
	{
		x += xInc;
		y += yInc;
		putpixel(x,y,GREEN);
	}
}

void main()
{
	clrscr();
	int gmode, gdriver = DETECT;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
	int xa, ya, xb, yb;
	cout<<"Enter the leftmost coordinate ==>> ";
	cin>>xa>>ya;
	cout<<"\nEnter the rightmost coordinate ==>> ";
	cin>>xb>>yb;
	DDA(xa, ya, xb, yb);
	getch();
	closegraph();
}