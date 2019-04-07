#include<iostream.h>
#include<graphics.h>
#include<conio.h>

void midpointcircle(int xc, int yc, int r)
{
	int x, y, p;
	x = 0;
	y = r;
	p = 1 - r;
	while (x <= y)
	{
		putpixel(xc + x, yc + y, GREEN);
		putpixel(xc + x, yc - y, GREEN);
		putpixel(xc - x, yc + y, GREEN);
		putpixel(xc - x, yc - y, GREEN);
		putpixel(xc + y, yc + x, GREEN);
		putpixel(xc + y, yc - x, GREEN);
		putpixel(xc - y, yc + x, GREEN);
		putpixel(xc - y, yc - x, GREEN);
		x++;
		if (p < 0)
		{
			p = p + 2*x + 1;
		}
		else
		{
			y--;
			p = p + 2*x - 2*y +1;
		}
	}
}

void main()
{
	clrscr();
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
	int xc, yc, r;
	cout<<"Enter the coordinates of centre of the circle ==>> ";
	cin>>xc>>yc;
	cout<<"\nEnter the radius ==>> ";
	cin>>r;
	midpointcircle(xc, yc, r);
	getch();
	closegraph();
}