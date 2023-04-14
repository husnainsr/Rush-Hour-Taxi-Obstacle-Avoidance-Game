//============================================================================
// Name        : Husnain Sattar 
// Author      : husnainsr
// Version     :	
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
//global variables
int obstacles[20][20]= {0};  //0 for empty space //1 for building //2 for person //3 for obstacle // 4 person dropoff //5 for box
bool pick=false;	// to identify weather person is sitting or not
int dropx,dropy;	// to store intial of x and y for drop off	
int checkx,checky; bool checklocation=false;	// to store intial of x and y to check the range of the person
int carwidth=50; 	//width of car
int score=0;	//to chcek score globaly
int dropcounter=0;	//check how many person are dropped 
int carcolor;	//color of car
float speed;	//to increase the speed of traffic
string name;
int seconds=0,minutes=0;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-410, width, -90, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
int xt1=100,yt1=900; //traffic intials
int xt2=-1000,yt2=500;	//traffic intials
int xt3=-1000,yt3=200;	//traffic intials
int xt4=-1000,yt4=800;
int xt5=-1000,yt5=100;

int xI = 50, yI = 950;	//taxi intials

void drawCar() {	//taxi is drawn here
	if(carcolor==1)
	{
		DrawCircle(xI+10,yI+10,10,colors[BLACK]);
		DrawCircle(xI+40,yI+10,10,colors[BLACK]);
		DrawRectangle(xI,yI+10,50,40,colors[RED]);
	
		// DrawSquare(xI, yI, carwidth, colors[RED]);
	}
	else if(carcolor==2)
	{
		DrawCircle(xI+10,yI+10,10,colors[BLACK]);
		DrawCircle(xI+40,yI+10,10,colors[BLACK]);
		DrawRectangle(xI,yI+10,50,40,colors[GOLD]);
	}
	glutPostRedisplay();
}
void trafficCar()	//all other traffic car is drawn here
{
		DrawCircle(xt1+10,yt1+10,10,colors[BLACK]);		//Drawing car first
		DrawCircle(xt1+40,yt1+10,10,colors[BLACK]);
		DrawRectangle(xt1,yt1+10,50,40,colors[BLUE]);
	if(dropcounter>=2)
	{
		DrawCircle(xt2+10,yt2+10,10,colors[BLACK]);	//Drawing car second
		DrawCircle(xt2+40,yt2+10,10,colors[BLACK]);
		DrawRectangle(xt2,yt2+10,50,40,colors[VIOLET]);
	}
	if(dropcounter>=4)
	{
		DrawCircle(xt3+10,yt3+10,10,colors[BLACK]);	//Drawing car third
		DrawCircle(xt3+40,yt3+10,10,colors[BLACK]);
		DrawRectangle(xt3,yt3+10,50,40,colors[BLUE]);
	}
	if(dropcounter>=6)
	{
		DrawCircle(xt4+10,yt4+10,10,colors[BLACK]);	//drawing car fourth
		DrawCircle(xt4+40,yt4+10,10,colors[BLACK]);
		DrawRectangle(xt4,yt4+10,50,40,colors[VIOLET]);
	}
	if(dropcounter>=7)
	{
		DrawCircle(xt5+10,yt5+10,10,colors[BLACK]);	//drawing car fifth
		DrawCircle(xt5+40,yt5+10,10,colors[BLACK]);
		DrawRectangle(xt5,yt5+10,50,40,colors[BLUE]);
	}
}
void boundries() // for taxi to not move outside grid
{ 
	if(xI<0)
		xI=carwidth+xI;
	if(xI>950)
		xI=xI-carwidth;
	if(yI<0)
		yI=carwidth+yI;
	if(yI>950)
		yI=yI-carwidth;
}
void drawgrid()	//drawing grid
{
	for(int i=0; i<=1000; i+=50)
	{
		DrawLine(i,0,i,1000,2,colors[BLACK]);
		DrawLine(0,i,1000,i,2,colors[BLACK]);
	}
		// DrawLine(0,0,1000,0,2,colors[BLACK]);
		// DrawLine(0,0,0,1000,2,colors[BLACK]);
		// DrawLine(0,1000,1000,1000,2,colors[BLACK]);
		// DrawLine(1000,1000,1000,0,2,colors[BLACK]);
}
void buildings()	//this will draw obstacles/buildings/persons etc
{
	//up left corner
	obstacles[0][19]=0;
	obstacles[0][18]=0;
	obstacles[1][19]=0;
	obstacles[1][18]=0;
		//bottom left corner
	obstacles[0][0]=0;
	obstacles[0][1]=0;
	obstacles[1][0]=0;
	obstacles[1][1]=0;
	//bottom right corner
	obstacles[18][0]=0;
	obstacles[19][0]=0;
	obstacles[18][1]=0;
	obstacles[19][1]=0;
	//up left corner
	obstacles[18][18]=0;
	obstacles[18][19]=0;
	obstacles[19][18]=0;
	obstacles[19][19]=0;

	for(int i=0; i<20; i++){	//drawing other objects
		for(int j=0; j<20; j++)
		{
			if(obstacles[i][j]==4)	//persons spawn 
				DrawSquare((i*50),(j*50),50,colors[GREEN]);
			if(obstacles[i][j]==1)	//buildings
				DrawSquare((i*50),(j*50),51,colors[BLACK]);
			if(obstacles[i][j]==3)	//tree
			{
				DrawRectangle(i*50+20,j*50,12,30,colors[BROWN]);
				DrawCircle(i*50+20,j*50+30,12,colors[GREEN]);
				DrawCircle(i*50+35,j*50+30,12,colors[GREEN]);
			}
			if(obstacles[i][j]==2)	//persons spawn
			{	
				DrawCircle(i*50+25,j*50+40,7,colors[BLACK]);
				DrawLine(i*50+25,j*50+10,i*50+25,j*50+35,1,colors[BLACK]);
				DrawLine(i*50+10,j*50,i*50+25,j*50+25,1.5,colors[BLACK]);
				DrawLine(i*50+35,j*50,i*50+25,j*50+25,1.5,colors[BLACK]);
			}
			if(obstacles[i][j]==5)	//box obstacle draw
			{
				DrawTriangle(i*50+10,j*50,i*50+40,j*50,i*50+25,j*50+45,colors[RED]);
				DrawRectangle(i*50+10,j*50,30,25,colors[BROWN]);
			}
		}
	}
}
void droprandom() //genrating new person randomly after dropoff or killed
{
	srand(time(NULL));
	do
	{
		dropx=GetRandInRange(0,20);
		dropy=GetRandInRange(0,20);
	} while ((obstacles[dropx][dropy]!=0));
}
//location to check person and dropoffk
void checkpersonrange()	//my 9 block sqare range check
{
	if(obstacles[(xI/50)-1][(yI/50)+1]==2)   //1st block
	{
		checklocation=true;
		checkx=(xI/50)-1;
		checky=(yI/50)+1;
	}
	else if(obstacles[(xI/50)][(yI/50)+1]==2)	    //2nd block
	{
		checklocation=true;
		checkx=(xI/50);
		checky=(yI/50)+1;
	}
	else if(obstacles[(xI/50)+1][(yI/50)+1]==2)	//3rd block
	{
		checklocation=true;
		checkx=(xI/50)+1;
		checky=(yI/50)+1;
	}
	else if(obstacles[(xI/50)-1][(yI/50)]==2)	    //4th block
	{
		checklocation=true;
		checkx=(xI/50)-1;
		checky=(yI/50);
	}
	else if(obstacles[(xI/50)+1][(yI/50)]==2)	    //6th block
	{
		checklocation=true;
		checkx=(xI/50)+1;
		checky=(yI/50);
	}
	else if(obstacles[(xI/50)-1][(yI/50)-1]==2)	//7th block
	{
		checklocation=true;
		checkx=(xI/50)-1;
		checky=(yI/50)-1;
	}
	else if(obstacles[(xI/50)][(yI/50)-1]==2)  	//8th block
	{
		checklocation=true;
		checkx=(xI/50);
		checky=(yI/50)-1;
	}
	else if(obstacles[(xI/50)+1][(yI/50)-1]==2)	//9th block
	{
		checklocation=true;
		checkx=(xI/50)+50;
		checky=(yI/50)-50;
	}
	else
		checklocation=false;

}

void movetraffice1()	//function to move traffic car 1 
{
	int randomnum;
	do		//deciding random movement
	{
		randomnum=rand()%4;
		if(randomnum==0)
			yt1+=50;
		else if(randomnum==1)
			yt1-=50;
		else if(randomnum==2)
			xt1+=50;
		else if(randomnum==3)
			xt1-=50;
	} while (obstacles[xt1/50][yt1/50]!=0);	//moving in free spaces only
	if(xt1<0)		//drawing boundries
		xt1=carwidth+xt1;
	if(xt1>950)
		xt1=xt1-carwidth;
	if(yt1<0)
		yt1=carwidth+yt1;
	if(yt1>950)
		yt1=yt1-carwidth;
	
	
	// cout<<"T ("<<xt1<<", "<<yt1<<" )"<<endl;
}
void movetraffice2()	//function to move traffic car 2
{
	int randomnum;
	do		//deciding random movement
	{
		randomnum=rand()%4;
		if(randomnum==0)
			yt2+=50;
		else if(randomnum==1)
			yt2-=50;
		else if(randomnum==2)
			xt2+=50;
		else if(randomnum==3)
			xt2-=50;
	} while (obstacles[xt2/50][yt2/50]!=0);  //moving in free spaces only
	if(xt2<0)	//drawing boundries
		xt2=carwidth+xt2;
	if(xt2>950)
		xt2=xt2-carwidth;
	if(yt2<0)
		yt2=carwidth+yt2;
	if(yt2>950)
		yt2=yt2-carwidth;
	if(xt2==xI && yt2==yI)		//collosion between taxi and cars
	{
		if (carcolor==1)
			score-=3;
		else if(carcolor==2)
			score-=2;
	}
	if((xt2==xI+50 && yt2==yI) || (xt2==xI && yt2==yI+50) || (xt2==xI-50 && yt2==yI) || (xt2==xI && yt2==yI-50))
	{
		score+=1;
	}
}
void movetraffic3()		//function to move traffic car 3
{
	int randomnum;
	do		//deciding random movement
	{
		randomnum=rand()%4;
		if(randomnum==0)
			yt3+=50;
		else if(randomnum==1)
			yt3-=50;
		else if(randomnum==2)
			xt3+=50;
		else if(randomnum==3)
			xt3-=50;
	} while (obstacles[xt3/50][yt3/50]!=0);  //moving in free spaces only
	if(xt3<0)	//drawing boundries
		xt3=carwidth+xt3;
	if(xt3>950)
		xt3=xt3-carwidth;
	if(yt3<0)
		yt3=carwidth+yt3;
	if(yt3>950)
		yt3=yt3-carwidth;
	if(xt3==xI && yt3==yI)	//collosion detection between cars and taxi
	{
		if (carcolor==1)
			score-=3;
		else if(carcolor==2)
			score-=2;
	}
	if((xt3==xI+50 && yt3==yI) || (xt3==xI && yt3==yI+50) || (xt3==xI-50 && yt3==yI) || (xt3==xI && yt3==yI-50))
	{
		score+=1;
	}
}
void movetraffic4()		//function to move traffic car 4
{
	int randomnum;
	do		//deciding random movement
	{
		randomnum=rand()%4;
		if(randomnum==0)
			yt4+=50;
		else if(randomnum==1)
			yt4-=50;
		else if(randomnum==2)
			xt4+=50;
		else if(randomnum==3)
			xt4-=50;
	} while (obstacles[xt4/50][yt4/50]!=0);  //moving in free spaces only
	if(xt4<0)	//drawing boundries
		xt4=carwidth+xt4;
	if(xt4>950)
		xt4=xt4-carwidth;
	if(yt4<0)
		yt4=carwidth+yt4;
	if(yt4>950)
		yt4=yt4-carwidth;
	if(xt4==xI && yt4==yI)	//collosion detection between cars and taxi
	{
		if (carcolor==1)
			score-=3;
		else if(carcolor==2)
			score-=2;
	}
	if((xt4==xI+50 && yt4==yI) || (xt4==xI && yt4==yI+50) || (xt4==xI-50 && yt4==yI) || (xt4==xI && yt4==yI-50))
	{
		score+=1;
	}
}
void movetraffic5()		//function to move traffic car 5
{
	int randomnum;
	do		//deciding random movement
	{
		randomnum=rand()%4;
		if(randomnum==0)
			yt5+=50;
		else if(randomnum==1)
			yt5-=50;
		else if(randomnum==2)
			xt5+=50;
		else if(randomnum==3)
			xt5-=50;
	} while (obstacles[xt5/50][yt5/50]!=0);  //moving in free spaces only
	if(xt5<0)	//drawing boundries
		xt5=carwidth+xt5;
	if(xt5>950)
		xt5=xt5-carwidth;
	if(yt5<0)
		yt5=carwidth+yt5;
	if(yt5>950)
		yt5=yt5-carwidth;
	if(xt5==xI && yt5==yI)	//collosion detection between cars and taxi
	{
		if (carcolor==1)
			score-=3;
		else if(carcolor==2)
			score-=2;
	}
	if((xt5==xI+50 && yt5==yI) || (xt5==xI && yt5==yI+50) || (xt5==xI-50 && yt5==yI) || (xt5==xI && yt5==yI-50))
	{
			score+=1;
	}
}


//////////////////
// MAIN CANVAS //
////////////////
void GameDisplay()/**/{
	glClearColor(1, 1,1, 0 ); //background color
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	if(minutes>=3)	//score greater then 100 this message will show
	{
		DrawString(0,500,"Game Over score =  "+to_string(score),colors[GOLD]);	//winning
		DrawString(0,400,"Press Enter to exit ",colors[RED]);	//winning

	}
	if(minutes<3)	//game grid will show when score is less than hundred
	{
		DrawString(50,1050,"Score = "+to_string(score),colors[RED]);	//display score
		DrawString(500,1050,""+to_string(minutes)+"m",colors[RED]);	//display score
		DrawString(550,1050,""+to_string(seconds)+"s",colors[RED]);	//display score


		DrawString(-300,800,"After 3mintues ",colors[GREEN]);
		DrawString(-300,750,"game will stop",colors[GREEN]);
		DrawString(-300,700,"automatically",colors[GREEN]);
		drawgrid();		//for grid
		buildings();	//for  buidlings and obstacles and person
		trafficCar();	//for other car
		drawCar();		//taxi
	}
		glutSwapBuffers(); // do not modify this line..

}
void NonPrintableKeys(int key, int x, int y) {		//movemnt for taxi
	int tempx,tempy;
	tempx=xI,tempy=yI;
	int speed;
	if(minutes<3)		//after score 100 taxi will stop
	{
		if (key == GLUT_KEY_LEFT ) 
		{
			xI -= 50;
		} 
		else if (key == GLUT_KEY_RIGHT )
		{
			xI += 50;
		}
		else if (key == GLUT_KEY_UP)
		{
			yI += 50;
		}
		else if (key == GLUT_KEY_DOWN)
		{
			yI -= 50;
		}
	}
		boundries();//for car to not go outside grid
			if(obstacles[xI/50][yI/50]==1)	//collsion detection for buildings
			{
					xI=tempx;
					yI=tempy;
			}
			if(obstacles[xI/50][yI/50]==3)	//collsion detection for trees
			{
					xI=tempx;
					yI=tempy;
					if (carcolor==1)
						score-=2;
					else if(carcolor==2)
						score-=4;
			}
			if(obstacles[xI/50][yI/50]==2)	//collsion detection for persons and respawrn
			{
				obstacles[xI/50][yI/50]=0;
				droprandom();
				obstacles[dropx][dropy]=2;
				score-=5;
			}
			if(obstacles[xI/50][yI/50]==5)	//collsion detection for box
			{
					xI=tempx;
					yI=tempy;
					score-=5;
			}
	glutPostRedisplay();

}

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 13/* Escape key ASCII*/) {
		fstream myfile;		

		myfile.open("highscore.txt", ios::app);

		myfile << name << "\t" << score << endl;
		
		
		myfile.close();
		
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == ' ') //Key for placing the bomb
	{
		//do something if space is pressed
		checkpersonrange();
		if(checklocation==true && pick==false)//pick up the person
		{ 
			pick=true;
			obstacles[checkx][checky]=0;	//make it the empty as free space
			droprandom();
			// cout<<"DROP ( "<<dropx*50<<", "<<dropy*50<<" )"<<endl;
			obstacles[dropx][dropy]=4;	//genrate the dropoff locarion
		}
		if(obstacles[xI/50][yI/50]==4)
		{
			pick=false;
			obstacles[xI/50][yI/50]=0;	//drop the person
			droprandom();
			obstacles[dropx][dropy]=2;	//to spawn new person
			score=score+10;
			dropcounter+=1;	
		}
	}
	glutPostRedisplay();
}


void Timer(int m) {

	// implement your functionality here
	// ()
	// NonPrintableKeys();
	//to increase car
	if(dropcounter>=0)
	{
		movetraffice1();
	}
	if(dropcounter>=2)
	{
		xt2=200,yt2=500;
		movetraffice2();
	}
	if(dropcounter>=4)
	{
		xt3=600,yt3=400;
		movetraffic3();
	}
	if(dropcounter>=6)
	{
		xt4=800,yt4=100;
		movetraffic4();
	}
	if(dropcounter>=7)
	{
		xt5=200,yt5=300;
		movetraffic5();
	}
	//to increase the speed of cars
	speed=1;
	if(dropcounter==2)
		speed=2;
	if(dropcounter==3)
		speed=3;
	if(dropcounter==4)
		speed=4;
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(3000/speed, Timer, 0);
}

void clock(int m)
{
	seconds++;
	if(seconds==60)
	{
		minutes+=1;
		seconds=0;
	}
	glutTimerFunc(1000,clock,0);
}

int main(int argc, char*argv[]) {
	int width = 1280, height = 1080; // i have set my window size to be 800 x 600
	int x,y,highscore;
	srand(time(NULL));
	for(int i=0; i<20; i++)		//random buildings dropoff
	{
		for(int j=0; j<3; j++)
		{
			x=GetRandInRange(0,20);
			y=GetRandInRange(0,20);	
			obstacles[x][y]=true;
		}
	}
		for(int i=0; i<5; i++)		//intial 5random persons
		{
			do
			{
				x=GetRandInRange(0,20);
				y=GetRandInRange(0,20);
			} while ((obstacles[x][y]==0));
			obstacles[x][y]=2;
		}
		for(int i=0; i<5; i++)		//random obstacles  treees
		{
			do
			{
				x=GetRandInRange(0,20);
				y=GetRandInRange(0,20);
			} while ((obstacles[x][y]!=0));
			obstacles[x][y]=3;
		}
		for(int i=0; i<5; i++)		//random obstacles box
		{
			do
			{
				x=GetRandInRange(0,20);
				y=GetRandInRange(0,20);
			} while ((obstacles[x][y]!=0));
			obstacles[x][y]=5;
		}
		cout<<"Enter your name : ";
		getline(cin,name);
	do {
		cout<<"Chooose : \n"
		<<"For RED    Enter = 1 \n"
		<<"For YELLOW Enter = 2 \n"
		<<"For Random Enter = 3 \n"
		<<"For Leader board = 4 \n"
		<<"Choice = ";
		cin>>carcolor;
	}while(carcolor!=1 && carcolor!=2 && carcolor!=3 && carcolor!=4);

	if(carcolor==4)
	{						//open file and display
		fstream myfile;
		string line;

		myfile.open("highscore.txt", ios::in);
		while(getline(myfile, line))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	if(carcolor==3)
	{
		carcolor=GetRandInRange(1,3);
	}
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("HUSNAIN"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.	
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(800.0, Timer, 0);
	glutTimerFunc(1000,clock,0);	//for timer

	// glutMouseFunc(MouseClicked);h
	// glutPassiveMotionFunc(MouseMoved); // Mouse
	// glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
		glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
