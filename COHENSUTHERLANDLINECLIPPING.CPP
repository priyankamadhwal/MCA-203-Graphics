#include<iostream.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<dos.h>

class Line
{
	public:

		float x1, y1, x2, y2;

		void setLineCoordinates()
		{
			cout<<"\nEnter the line coordinates :\n";
			cout<<"x1, y1 ==>> ";
			cin>>x1>>y1;
			cout<<"x2, y2 ==>> ";
			cin>>x2>>y2;
		}

		void drawLine()
		{
			setcolor(WHITE);
			line(x1,y1,x2,y2);
		}
};

class Window
{
	public:
		float xmin, ymin, xmax, ymax;

		void setWindowCoordinates()
		{
			cout<<"Enter the coordinates of rectangular clip window :\n";
			cout<<"xmin, ymin ==>> ";
			cin>>xmin>>ymin;
			cout<<"xmax, ymax ==>> ";
			cin>>xmax>>ymax;
		}

		void drawWindow()
		{
			setcolor(RED);
			rectangle(xmin, ymin, xmax, ymax);
		}
};

class RegionCode
{
	public:
		int bit[4];
		RegionCode()
		{
			for (int i=0; i<4; i++)
				bit[i] = 0;
		}
		int isZero()
		{
			int flag = 1;
			for (int i=0; i<4; i++)
				if (bit[i] != 0)
				{
					flag = 0;
					break;
				}
			return flag;
		}
		void getLogicalAnd(RegionCode RC1, RegionCode RC2)
		{
			for (int i=0; i<4; i++)
			{
				if (RC1.bit[i] == 1 && RC2.bit[i] == 1)
					bit[i] = 1;
				else
					bit[i] = 0;
			}
		}
		void getRegionCode(Window W, int x, int y)
		{
			//Left
			if (x < W.xmin)
				bit[0] = 1;
			//Right
			if (x > W.xmax)
				bit[1] = 1;
			//Bottom
			if (y < W.ymin)
				bit[2] = 1;
			//Top
			if (y > W.ymax)
				bit[3] = 1;
		}

};

void calculateIntersectingPoints(Window W, Line &L)
{
	RegionCode RC1, RC2, RC;
	RC1.getRegionCode(W,L.x1,L.y1);
	RC2.getRegionCode(W,L.x2,L.y2);
	if (!RC1.isZero())
	{
		float m;
		float x = L.x1;
		float y = L.y1;
		float dx = L.x2 - L.x1;
		if (dx!=0)
			m = (L.y2-L.y1)/(L.x2-L.x1);
		if (RC1.bit[0] == 1)
		{
			x = W.xmin;
			y = L.y1+(m*(x-L.x1));
		}
		else if (RC1.bit[1] == 1)
		{
			x = W.xmax;
			y = L.y1+(m*(x-L.x1));
		}
		else if (RC1.bit[2] == 1)
		{
			y = W.ymin;
			if (dx!=0)
				x = L.x1+((y-L.y1)/m);
		}
		else if (RC1.bit[3] == 1)
		{
			y = W.ymax;
			if (dx!=0)
				x = L.x1+((y-L.y1)/m);
		}
		L.x1 = x;
		L.y1 = y;
	}
	if (!RC2.isZero())
	{
		float m;
		float x = L.x2;
		float y = L.y2;
		float dx = L.x2 - L.x1;
		if (dx!=0)
			m = (L.y2-L.y1)/(L.x2-L.x1);
		if (RC2.bit[0] == 1)
		{
			x = W.xmin;
			y = L.y1+(m*(x-L.x1));
		}
		else if (RC2.bit[1] == 1)
		{
			x = W.xmax;
			y = L.y1+(m*(x-L.x1));
		}
		else if (RC2.bit[2] == 1)
		{
			y = W.ymin;
			if (dx!=0)
				x = L.x1+((y-L.y1)/m);
		}
		else if (RC2.bit[3] == 1)
		{
			y = W.ymax;
			if (dx!=0)
				x = L.x1+((y-L.y1)/m);
		}
		L.x2 = x;
		L.y2 = y;
	}
}

int clipLine(Window W, Line &L)
{
	RegionCode RC1, RC2, RC;
	RC1.getRegionCode(W,L.x1,L.y1);
	RC2.getRegionCode(W,L.x2,L.y2);
	RC.getLogicalAnd(RC1, RC2);

	//If line is completely inside.
	if(RC1.isZero() && RC2.isZero())
		return 1;
	//If line is completely outside.
	else if (!RC.isZero())
		return 0;
	//If line is partially inside / partially outside.
	else
	{
		calculateIntersectingPoints(W,L);
		clipLine(W,L);
		return 1;
	}
}


void main()
{
	int gdriver = DETECT, gmode;

	Window W;
	W.setWindowCoordinates();

	Line L;
	L.setLineCoordinates();

	clrscr();
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

	cout<<"\t\tUNCLIPPED LINE";
	W.drawWindow();
	L.drawLine();

	getch();
	cleardevice();

	cout<<"\t\tCLIPPED LINE";
	W.drawWindow();
	if (clipLine(W,L))
		L.drawLine();
	getch();
	closegraph();
}