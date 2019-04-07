#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>

void car(int i, int color)
{
	setcolor(color);
	line(0+i,300,30+i,300);		//Bottom line 1
	arc(50+i,300,0,180,20);		//Bottom arc 1
	circle(50+i,300,14);		//Tyre 1
	circle(50+i,300,12);
	circle(50+i,300,3);
	line(70+i,300,110+i,300);	//Bottom line 2
	arc(130+i,300,0,180,20);	//Bottom arc 2
	circle(130+i,300,14);	        //Tyre 2
	circle(130+i,300,12);
	circle(130+i,300,3);
	line(150+i,300,180+i,300);	//Bottom line 3
	line(0+i,300,0+i,280);		//Vertical line 1
	line(180+i,300,180+i,280);	//Vertical line 2
	line(0+i,280,25+i,260);		//Tilt line 1
	line(180+i,280,155+i,260);	//Tilt line 2
	arc(90+i,260,0,180,65);		//Upper arc

	//Window
	arc(90+i,260,0,180,50);
	arc(90+i,260,0,180,47);
	line(40+i,260,140+i,260);
	line(40+i,257,140+i,257);
	line(90+i,257,90+i,213);
	setcolor(WHITE);
}

void road(int i, int color)
{
	setcolor(color);
	line(0,290,0+i,290);
	line(180+i,290,800,290);
	line(0, 380,800,380);
	setcolor(WHITE);
}

void trafficLight(char color)
{
	//Traffic light
	line(570,80,630,80);
	line(574,84,626,84);
	line(570,80,570,170);
	line(574,84,574,166);
	line(630,80,630,170);
	line(626,84,626,166);
	line(570,170,630,170);
	line(574,166,626,166);
	line(597,170,597,290);
	line(603,170,603,290);
	circle(600,150,10);
	circle(600,100,10);
	circle(600,125,10);
	if (color==NULL)
	{
		setfillstyle(SOLID_FILL,RED);
		floodfill(600,100,15);        	//15->White(boundary)
		delay(1500);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,100,15);
		setfillstyle(SOLID_FILL,YELLOW);
		floodfill(600,125,15);
		delay(1500);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,125,15);
		setfillstyle(SOLID_FILL,GREEN);
		floodfill(600,150,15);
	}
	else if (color=='r')
	{
		setfillstyle(SOLID_FILL,RED);
		floodfill(600,100,15);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,125,15);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,150,15);
	}
	else if (color=='y')
	{
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,100,15);
		setfillstyle(SOLID_FILL,YELLOW);
		floodfill(600,125,15);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,150,15);
	}
	else if (color=='g')
	{
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,100,15);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(600,125,15);
		setfillstyle(SOLID_FILL,GREEN);
		floodfill(600,150,15);
	}
}

void main()
{
	clrscr();
	int gd=DETECT, gm;
	initgraph(&gd, &gm,"C:\\TURBOC3\\BGI");
	int i=0;
	char color = NULL;
	car(i,15);
	road(i,15);
	trafficLight(color);
	color='g';
	cleardevice();
	cout<<"Press \"enter\" twice to exit!";
	cout<<"\nPress \"r\" for RED, \"y\" for YELLOW and \"g\" for GREEN traffic light color.";
	while(1)
	{
		while(!kbhit())
		{
			car(i,0);
			road(i,0);
			trafficLight(color);
			if (color=='g')
				i++;
			car(i,15);
			road(i,15);
			delay(30);
		}
		color=getch();
		if (color==13)
			break;
	}

	getch();
	closegraph();
}