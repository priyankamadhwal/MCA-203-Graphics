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

int checkLine(float p, float q, float &u1, float &u2)
{
	int flag = 1;
	float r = q/p;

	if(p < 0)
	{
		if (r > u2)
			flag=0;
		else if(r > u1)
			u1=r;
	}
	else if(p > 0)
	{
		if(r < u1)
			flag=0;
		else if(r < u2)
			u2=r;
	}
	else
	{
		if(q < 0)
			flag=0;
	}
	return flag;
}

int clipLine(Window W,Line &L)
{
	float u1, u2, dx, dy, p[4], q[4];

	u1 = 0;
	u2 = 1;

	dx = L.x2-L.x1;
	dy = L.y2-L.y1;

	p[0] = -dx;
	p[1] = dx;
	p[2] = -dy;
	p[3] = dy;

	q[0] = L.x1-W.xmin;
	q[1] = W.xmax-L.x1;
	q[2] = L.y1-W.ymin;
	q[3] = W.ymax-L.y1;

	int checkFlag = 1;
	for (int i=0; i<4; i++)
	{
		if (!checkLine(p[i],q[i],u1,u2))
		{
			checkFlag = 0;
			break;
		}
	}

	if(checkFlag)
	{
		if(u2 < 1)
		{
			L.x2=(L.x1+(u2*dx));
			L.y2=(L.y1+(u2*dy));
		}
		if(u1>0)
		{
			L.x1+=(u1*dx);
			L.y1+=(u1*dy);
		}
		return 1;
	}

	return 0;
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