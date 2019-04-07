#include<iostream.h>
#include<conio.h>
#include<graphics.h>

#define round(a) ((int)(a+0.5))
#define INFINITE 0

class Polygon
{
	public:

		int n;
		float poly[100];

		void setPolygonCoordinates()
		{
			cout<<"\n\nEnter the polygon to be clipped :";
			cout<<"\nNumber of sides ==>> ";
			cin>>n;
			for(int i=0; i<2*n; i+=2)
			{
				cout<<"Enter the coordinates of vertex "<<(i/2+1)<<" : ";
				cin>>poly[i]>>poly[i+1];
			}
			poly[i]=poly[0];
			poly[i+1]=poly[1];
		}

		void drawPolygon()
		{
			int polyInt[100];
			for(int i=0; i<2*(n+1); i++)
				polyInt[i]=round(poly[i]);
			setcolor(WHITE);
			fillpoly(n,polyInt);
		}
} P;

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
} W;

void leftClip()
{
	int i,j=0,count=0;
	float m, temp[100];

	for(i=0; i<2*P.n; i+=2)
	{
		float x1 = P.poly[i], y1 = P.poly[i+1], x2 = P.poly[i+2], y2 = P.poly[i+3];

		if(x2 - x1)
			m = (y2-y1) / (x2-x1);
		else
			m = INFINITE;

		if(x1 < W.xmin && x2 < W.xmin)
		{
			//Both points outside. Do not store any vertices.
		}
		else if(x1 >= W.xmin && x2 >= W.xmin)
		{
			//Both points inside. Store second vertex.
			temp[j] = x2;
			temp[j+1] = y2;
			j+=2;
			count++;
		}
		else if(x1 < W.xmin && x2 >= W.xmin)
		{
			//Outside to inside. Store intersection and second vertex.
			temp[j] = W.xmin;
			temp[j+1] = y1 + m*(W.xmin-x1);
			temp[j+2] = x2;
			temp[j+3] = y2;
			j+=4;
			count+=2;
		}
		else
		{
			//Inside to outside. Store intersection only.
			temp[j] = W.xmin;
			temp[j+1] = y1 + m*(W.xmin-x1);
			j+=2;
			count++;
		}
	}

	P.n = count;

	//Store 1st vertex as last.
	temp[j]=temp[0];
	temp[j+1]=temp[1];

	for(i=0; i < 2*(P.n+1); i++)
		P.poly[i] = temp[i];
}

void rightClip()
{
	int i,j=0,count=0;
	float m, temp[100];
	for(i=0; i<2*P.n; i+=2)
	{
		float x1 = P.poly[i], y1 = P.poly[i+1], x2 = P.poly[i+2], y2 = P.poly[i+3];

		if(x2 - x1)
			m = (y2-y1) / (x2-x1);
		else
			m = INFINITE;

		if(x1 > W.xmax && x2 > W.xmax)
		{
			//Both points outside. Do not store any vertices.
		}
		else if(x1 <= W.xmax && x2 <= W.xmax)
		{
			//Both points inside. Store second vertex.
			temp[j] = x2;
			temp[j+1] = y2;
			j+=2;
			count++;
		}
		else if(x1 > W.xmax && x2 <= W.xmax)
		{
			//Outside to inside. Store intersection and second vertex.
			temp[j] = W.xmax;
			temp[j+1] = y1 + m*(W.xmax-x1);
			temp[j+2] = x2;
			temp[j+3] = y2;
			j+=4;
			count+=2;
		}
		else
		{
			//Inside to outside. Store intersection only.
			temp[j] = W.xmax;
			temp[j+1] = y1 + m*(W.xmax-x1);
			j+=2;
			count++;
		}
	}

	P.n = count;

	//Store 1st vertex as last.
	temp[j]=temp[0];
	temp[j+1]=temp[1];

	for(i=0; i < 2*(P.n+1); i++)
		P.poly[i] = temp[i];
}

void bottomClip()
{
	int i,j=0,count=0;
	float m, temp[100];

	for(i=0; i<2*P.n; i+=2)
	{
		float x1 = P.poly[i], y1 = P.poly[i+1], x2 = P.poly[i+2], y2 = P.poly[i+3];

		if(x2 - x1)
			m = (y2-y1) / (x2-x1);
		else
			m = INFINITE;

		if(y1 < W.ymin && y2 < W.ymin)
		{
			//Both points outside. Do not store any vertices.
		}
		else if(y1 >= W.ymin && y2 >= W.ymin)
		{
			//Both points inside. Store second vertex.
			temp[j] = x2;
			temp[j+1] = y2;
			j+=2;
			count++;
		}
		else if(y1 < W.ymin && y2 >= W.ymin)
		{
			//Outside to inside. Store intersection and second vertex.
			temp[j] = x1 + m*(W.ymin-y1);
			temp[j+1] = W.ymin;
			temp[j+2] = x2;
			temp[j+3] = y2;
			j+=4;
			count+=2;
		}
		else
		{
			//Inside to outside. Store intersection only.
			temp[j] = x1 + m*(W.ymin-y1);;
			temp[j+1] = W.ymin;
			j+=2;
			count++;
		}
	}

	P.n = count;

	//Store 1st vertex as last.
	temp[j]=temp[0];
	temp[j+1]=temp[1];

	for(i=0; i < 2*(P.n+1); i++)
		P.poly[i] = temp[i];
}

void topClip()
{
	int i,j=0,count=0;
	float m, temp[100];

	for(i=0; i<2*P.n; i+=2)
	{
		float x1 = P.poly[i], y1 = P.poly[i+1], x2 = P.poly[i+2], y2 = P.poly[i+3];

		if(x2 - x1)
			m = (y2-y1) / (x2-x1);
		else
			m = INFINITE;

		if(y1 > W.ymax && y2 > W.ymax)
		{
			//Both points outside. Do not store any vertices.
		}
		else if(y1 <= W.ymax && y2 <= W.ymax)
		{
			//Both points inside. Store second vertex.
			temp[j] = x2;
			temp[j+1] = y2;
			j+=2;
			count++;
		}
		else if(y1 > W.ymax && y2 <= W.ymax)
		{
			//Outside to inside. Store intersection and second vertex.
			temp[j] = x1 + m*(W.ymax-y1);
			temp[j+1] = W.ymax;
			temp[j+2] = x2;
			temp[j+3] = y2;
			j+=4;
			count+=2;
		}
		else
		{
			//Inside to outside. Store intersection only.
			temp[j] = x1 + m*(W.ymax-y1);;
			temp[j+1] = W.ymax;
			j+=2;
			count++;
		}
	}

	P.n = count;

	//Store 1st vertex as last.
	temp[j]=temp[0];
	temp[j+1]=temp[1];

	for(i=0; i < 2*(P.n+1); i++)
		P.poly[i] = temp[i];
}

void main()
{
	clrscr();

	W.setWindowCoordinates();

	P.setPolygonCoordinates();

	int gdriver=DETECT,gmode;
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

	cout<<"\t\tUNCLIPPED POLYGON";
	W.drawWindow();
	P.drawPolygon();

	getch();
	cleardevice();

	for (int i=0; i<4; i++)
	{
		char* msg;
		switch (i)
		{
			case 0 : leftClip();
				 msg="LEFT CLIP"; break;
			case 1 : rightClip();
				 msg="RIGHT CLIP"; break;
			case 2 : bottomClip();
				 msg="BOTTOM CLIP"; break;
			case 3 : topClip();
				 msg="TOP CLIP"; break;
		}
		cout<<msg;
		W.drawWindow();
		P.drawPolygon();
		getch();
		cleardevice();
	}

	cout<<"\tCLIPPED POLYGON";
	W.drawWindow();
	P.drawPolygon();

	getch();
	closegraph();
}