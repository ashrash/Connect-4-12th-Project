	/* 2012 Computer science Project.*/

  /*	        Connect 4                        */

#include"graphics.h"
#include"fstream.h"
#include"process.h"
#include"string.h"
#include"stdlib.h"
#include"conio.h"
#include"stdio.h"
#include"math.h"
#include"bios.h"
#include"dos.h"

/*
  Pre-Processor Directives
  With their Bioskey values...
			   */
#define Up_Arrow     18432
#define Down_Arrow   20480
#define Right_Arrow  19712
#define Left_Arrow   19200
#define F1  	     15104
#define Enter         7181
#define ESC  	       283

//Radius of the circle...//

#define r               25


int connect[7][7],play=0;
int circle_no=1,invalid=0;
int index1=0,index2=0,cl1=1;
int cl2=4,fl=1,i=0,j=0,a;
int flag=0,key=0;
int controller=1,flag1=0;

const float soun[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94};

long double k;

char pl1[50]={"blue"},pl2[50]={"reddd"},file[150];

	void st(void);//FUNCTION Initializes the variables......
	void end(int);//Ends the program by declaring.... the result.....
	void main(int);//..
	void cred(void);// Rolls...the credits....
	void remov(void);//Removes the saved file....
	void color(void);/// Player can change the checker colour...
	void title(void);//Shows the title ....
	void screen(void);// Initializes graphics....
	void sounds(void);// Option to play with sounds...
	void Userdoc(void);//Shows Instructions.....
	void showsav(void);// Shows...the list of saved games...in this computer..
	void circleno(void);//finds circle Number...
	void opensave(void);// Opens a saved file...
	void validmov(void);// Validates the move done by the player...
	void getplname(void);//Gets... player name...
	void drawcircle(int);/// Draws... Circle..for..the game..[Mouse];
	void drawmenu(int,int);//Draws the main menu...
	void drawcircle(double);/// Draws... Circle..for..the game..[Keyboard];
	void findcir_no(int,int);//Using the click...done by user..fn finds the circle number..

	int mmenu(int);//Navigation,,, of the main menu done here....
	int result(void);//Checks..the result[Who wins the game..]
	int menu(int,int);//Decides....What function to be called..
	int gamesave(void);//Saves the game....
	int playerturn(int);//Player ///plays//[Mouse]
	int playerturn(double);////Player ///plays//[KeyBoard]
	int validclick(int,int);//Checks if the click is done into the circle..
	int mouse(int &, int &, int &);//Navigation of the mouse....

 //Mouse Functions


void findcir_no(int x,int y)
{
	int c=0,l=0;
	for(j=70;j<460;j+=60)
	{
		for(i=80;i<480;i+=60)
		{
			c++;
/*Radius=25;*/		if(x<i+r && x>i-r && y<j+r && y>j-r)
			{

				circle_no=c;//Circle number..is found..
				l=1;//flag...variable to break outer for(;;);
				break;
			}


		}
		if(l)//outer for(;;) is broken...
			break;
	}
	i=0,j=0;//resetting variables,,,
}
int validclick(int x1,int y1)
{
	int x2,y2;
	long double dist;
	for(x2=70;x2<460;x2+=60)
	{
		for(y2=80;y2<480;y2+=60)
		{
			dist=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
			/*In Mathematics.....
			 Distance formula*/
			if(dist<=r+1)//Checks if it is inside the circle..
				return dist;
		}

	}
	if(x1>480 && x1<580 && y1>10 && y1<40)//Checking if click is inside
	{                                     //the rectangle;
		mmenu(0);
		dist=10;
		drawcircle(5);
		// To Go to Main menu//
		/*    -----------
		     |  OPTIONS  |   If Player clicks
		      -----------    the player
				     would be
				     Redirected to
				     main menu;
					  */
	}
	return dist;
}
void drawcircle(int k)//Func...overloaded
{			//with (int)... for mouse....
	int l;// l & k used for index num..
	cleardevice();
	settextstyle(1,0,1);//Normal text....
	gotoxy(1,1);
	if(flag)//Flag a global var..if(flag!=0)
		cout<<"Invalid Move .,,,,";
	else
		if(play%2==0)//If play...is even....
			cout<<pl1<<"'s turn :    "; /// Pl1 turn...
		else
			cout<<pl2<<"'s turn :    ";/// Pl2 turn....
	rectangle(480,40,580,10);//Rectangle drawn....for Options..
	outtextxy(480,10,"  Options");// Options...
	for(j=70,l=0;j<460;j+=60,l++)//j=70,i=80,,...center
	{				//points..of circles..
		for(i=80,k=0;i<480;i+=60,k++)
		{
			if(connect[k][l]==0)
				circle(j,i,r);//Blank circle....
			else if(connect[k][l]==1)//== 1 Pl 1...
			{
				setfillstyle(1,cl1);//Pl 1 colour..
				fillellipse(j,i,r,r);//filling colour...
			}
			else if(connect[k][l]==2)//== 2 Pl2...
			{
				setfillstyle(1,cl2);//Pl 2 colour...
				fillellipse(j,i,r,r);//Filling color...
			}
		}
	}

}
int playerturn(int kk)//Func.. overloaded with (int)
{			//for mouse....
	int x=0,y=0,cl=0,re=0,pl=0;//x,y are the initial co-ordinates..
	/*re result,
	 cl click,
	 pl flag*/
	for(kk=1;kk<=49;)       //Player plays...loop starts....
	{
		flag=0;//For invalid move...
		if(play>=7)//checking the result....
		//A fair game can be finished in minimum 7 moves(in total) .
		{
			re=result();
			if(re==1)//denotes player 1
				return 1;
			if(re==2)//denotes player 2
				return 2;
		}
		for(i=0;i<7;i++)//checking...for available blank checkers...
		{
			for(j=0;j<7;j++)
			{
				if(connect[i][j]==0)
				{
					pl=1;//if any... pl=1;
					break;
				}
			}
		}
		mouse(x,y,cl);//Displaying mouse..
		// x,y& cl  passed by reference,,,
		a=validclick(x,y);//checking the click..
				//whether it is inside the circle...
		if(a>26)//if outside the circle
		{	// Radius=25
			flag=1;//Invalid move...indicator..
			drawcircle(5);//to print Invalid move.
			continue;//with all the circles...
		}
		else
			kk++,play++;//incrementing after every valid play...
		if(pl)//if any circle blank.//
		{
			if(cl==1)//..If circle is clicked...
			{
				findcir_no(x,y);//finding circle number..
				validmov();//bringing checker from top to down..
				circleno();//fixing the index values..of the circle
					//and assigning.. 1 or 2 to connect[7][7]...
				drawcircle(5);//Re-drawing the circles...
			}
		}
		else
			return 0;// if all the circles are occupied...
	}
	return -1;
}

union REGS in,out;//Mouse...

int callmouse()//calls the mouse..
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}
void mouseposi(int &xpos,int &ypos,int &click)//gets mouse position...
{
	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}
int mousehide()//hiding mouse.. after click....
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}
void setposi(int &xpos,int &ypos)//Setting mouse position...
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}
int mouse(int &xc,int &yc,int &clk)//mouse func which calls the above function./.
{
	int a=xc,b=yc;// 0,0
	setposi(a,b);//sets position (0,0)
	callmouse();// calls the mouse....
	mouseposi(xc,yc,clk);// positioning the mouse...
	do
	{
		mouseposi(xc,yc,clk);
		if(clk==1) //if mouse is clicked...
		{
			if(fl==1)//flag variable for sound...
				sound(soun[random(7)]*4);
			delay(200);//delays 2 sec(s),,,
				  //or else it would take
				  //one click as 4-5 clicks
			nosound(); //stop sound
			cleardevice();
			break;
		}
	}while(1);//Infinite loop
	mousehide();// hiding the mouse....
	return 0;
}

 // Key Board Controller Functions.
 

void drawcircle(double kk)//Func overloaded with double.
{			 //for key board....
	int i,j,l,k;
	kk=0;
	cleardevice();
	gotoxy(1,1);
	if(play%2==0)// checking the player's turn...
		cout<<pl1<<"'s turn : ";
	else
		cout<<pl2<<"'s turn : ";
	for(i=80,k=0;i<480;i+=60,k++)
	{
		for(j=70,l=0;j<460;j+=60,l++)
		{
			kk++;
			if(circle_no==kk)//cursor..
			{
				settextstyle(0,0,1);
				outtextxy(j,i,"_");//Displaying the cursor
				circle(j,i,r);
			}
			if(connect[k][l]==0)//blank circle..
				circle(j,i,r);
			else if(connect[k][l]==1)//Player 1's checker
			{
				setfillstyle(1,cl1);
				fillellipse(j,i,r,r);
			}
			else if(connect[k][l]==2)//Player 2's checker
			{
				setfillstyle(1,cl2);
				fillellipse(j,i,r,r);
			}
		}
	}
}
int playerturn(double kk)//Func.. overloaded with (double)
{				//for keyboard
	int re=0,pl=0,i,j;
	kk=2.0;
	for(;;)
	{
		invalid=0;
		for(i=0;i<7;i++)
		{
			for(j=0;j<7;j++)
			{
				if(connect[i][j]==0)
					pl=1;
			}
		}
		if(pl)
		{
			key=bioskey(0);//Getting Bios key values..
			if(key==Enter)/*Bios key of "Enter" to choose the circle.*/
			{
				if(fl==1)
					sound(soun[random(7)]*4);

				validmov();// validating the move..
				circleno();// finds the index number..
				drawcircle(kk);//Drawing circle
				delay(150);
				nosound();
				if(::play>=7)
				{
					re=result();//Checks the result!..
					if(pl)
					{
						if(re==1)
							return 1;
						if(re==2)
							return 2;
					}
				}
			}
			else if(key==Up_Arrow) /*UP Cursor movement*/
			{
				if(circle_no-7<1)
					circle_no=circle_no+49+1;
				//if the player clicks up staying on the
				//top most circle,to bring the curcor down...
				circle_no-=7;// 7 circles back
				drawcircle(kk);
			}
			else if(key==Down_Arrow) /*down Cursor movement*/
			{
				if(circle_no+7>49)
					circle_no=circle_no-49-1;
				circle_no+=7;
				drawcircle(kk);
			}
			else if(key==Right_Arrow) /*right Cursor movement*/
			{
				circle_no++;
				drawcircle(kk);
			}
			else if(key==Left_Arrow) /*left Cursor movement*/
			{

				circle_no--;
				drawcircle(kk);
			}
			else if(key==F1 || key==ESC)//Main menu..
			{
				mmenu(0);
				drawcircle(kk);
			}
		}
		else
			return 0;

	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void screen(char st[30])//initializing graphics
{

	restorecrtmode();
	int graph=DETECT,mode;
	initgraph(&graph, &mode,st);

}
void init()//decting error in initializing graphics
{
	int errorcode;
	char str[30];
	strcpy(str,"e:\\tc\\bgi");
	screen(str);
	while(1)
	{
		errorcode=graphresult();
		if(errorcode != grOk)
		{
			printf("Graphics error: %s\n", grapherrormsg(errorcode));
			printf("\nPress any key...");
			cout<<"\Give the BGI folder Location..example d:\\tc\\bgi...";
			cin>>str;//Getting the bgi folder location...
			clrscr();
			screen(str);
		}
		else
			break;
	}
}
void main(int a)
{
	clrscr();
	init();//initializing graphics
	int overload1=1;//For mouse...functions
	double overload2=2.0;//For Key board...functions
	int f=1,re=0;//flag
	nosound();
	if(0)//if main function called...from some other function.....
		title();//Graphics simulation of the title..
	f=mmenu(1);//Main Menu
	//mmenu is passed 1
	// meaning:- normal main menu without some options
	//  	       	1) Continue game 2)Save game..
	if(f)
	{
		if(controller==1)// if controller is mouse
		{
			drawcircle(overload2);
			re=playerturn(overload2);//MOUSE configuration.
		}
		else
		{
			drawcircle(overload1);
			re=playerturn(overload1);//Keyboard configuration.
		}
		end(re);//Result is declared...
	}
}

//	COMMON FUNCTIONS FOR MOUSE & KEY BOARD 
	
void dc(int m)//Displaying the main menu...
{
	cleardevice();
	outtextxy(130,200,"Do You want to switch controller...???");
	outtextxy(130,240,"Choose the controller you want........\n\n");
	if(m==1)
	{
		setcolor(LIGHTGREEN);
		outtextxy(220,300,"      Key Board ");
	}
	else
	{
		setcolor(15);
		outtextxy(150,300,"Key board ");
	}
	if(m==2)
	{
		setcolor(LIGHTGREEN);
		outtextxy(220,400,"    Mouse ");
	}
	else
	{
		setcolor(15);
		outtextxy(150,400,"Mouse ");
	}
	setcolor(15);
}
void switchc()//Switching controllers...
{
	int m=1;
	clrscr();
	dc(m);
	for(;;)
	{
		key=bioskey(0);//Getting the key...
		if(key==Enter)
		{
			controller=m;
			return;
		}
		if(key==Up_Arrow) /*UP Cursor movement*/
		{
			clrscr();
			m--;
			if(m<1)
				m=2;
			else
				m=1;
			dc(m);
		}
		else if(key==Down_Arrow) /*down Cursor movement*/
		{
			clrscr();
			m++;
			if(m>2)
				m=1;
			else
				m=2;
			dc(m);
		}
	}


}
int menu(int start,int b)//Assigning the functions
{				// to the appropriate options
	switch(start)
	{
		case 10:exit(0);   				 //Exit
		case 9:cred();      mmenu(b); return 1;//Displaying credits..
		case 8:color();     mmenu(b); return 1;// Checker color
		case 7:sounds();   mmenu(b); return 1;//Enable or disable sounds..
		case 6:switchc();  mmenu(b); return 2;//Switching controller
		case 5:Userdoc(); mmenu(b); return 1;//INSTRICTIONS
		case 4:showsav();  mmenu(b); return 1;//Shows list of saved files..
		case 3:remov();     mmenu(b); return 1;//Shows list of saved files..
		case 2:opensave(); //opens the file,.,
		       if(flag1)	  mmenu(b);//if open failed..
		       else				return 1;//open sucess..
		case 1:st();	return 2;//INITIALIZING the variables..		
		case 0:gamesave(); mmenu(b); return 1;//SAVING game..
		case -1:cleardevice();return 1;//Continue the game...
	}

	return 0;
}
int mmenu(int a)
{// a-Location variable shows the location from which the function is called..
	int move=a,b=a;//copy of a...
	if(!a)//if a==0;
	{
		move=-1;//to display some options...
		b=-1;//B is a copy of a...
	}
	drawmenu(move,a);// drawing the menu...
	for(;;)
	{
		key=bioskey(0);
		if(key==Enter)
			return menu(move,a);//Returning the return value
						// form menu...
		if(key==Up_Arrow) /*UP Cursor movement*/
		{
			cleardevice();
			move--;
			if(move>10)
				move=b;//goes to the top....
			else if(move<b)
				move=10;//goes to the end...
			if(!a)
				if(move==6||move==9)//Not to display..
						// Switch controller...
						// 	Credits
					move--;
			drawmenu(move,a);
		}
		else if(key==Down_Arrow) /*down Cursor movement*/
		{
			cleardevice();
			move++;
			if(move>10)
				move=b;
			else if(move<b)
				move=10;
			if(!a)
				if(move==6||move==9)
					move++;
			drawmenu(move,a);
		}
	}
}
void drawmenu(int move,int b)
{
	int a,j=150,s=100,s1=40;
	int d=30;
	textcolor(15);
	cleardevice();
	highvideo();
	gotoxy(1,1);
	if(b)
		cout<<"\t\t\t--->Main Menu<---\n";
	else
		cout<<"\t\t\t--->Options [sub menu]<---\n";

	cout<<"\n\t\tUse Arrow Keys to Navigate..."<<(char)24<<(char)25;
	settextstyle(1,0,1);
	if(!b)//if b==0  when function is called in the middle of the game...
	{
					//Continue game,
		if(move==-1)            // Save game should not be displayed
		{                  //in the main menu before starting the game...
			setcolor(LIGHTGREEN);//Highlighting the option
			outtextxy(j+s,d+=s1 ,"Continue Game ");
		}
		else
		{
			setcolor(15);
			outtextxy(j,d+=s1 ,"Continue Game ");
		}
		if(move==0)
		{
			setcolor(LIGHTGREEN);//Highlighting the option
			outtextxy(j+s,d+=s1 ,"Save game ");
		}
		else
		{
			setcolor(15);
			outtextxy(j,d+=s1 ,"Save game ");
		}
	}
	if(move==1)
	{
		setcolor(LIGHTGREEN);//Highlighting the option
		outtextxy(j+s,d+=s1 ,"New Game ");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"New Game ");
	}
	if(move==2)
	{
		setcolor(LIGHTGREEN);//Highlighting the option
		outtextxy(j+s,d+=s1 ,"Load Game ");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"Load Game ");
	}
	if(move==3)
	{
		setcolor(LIGHTGREEN);
		outtextxy(j+s,d+=s1 ,"Delete File");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"Delete File");
	}
	if(move==4)
	{
		setcolor(LIGHTGREEN);
		outtextxy(j+s,d+=s1 ,"Saved Games ");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"Saved Games ");
	}
	if(move==5)
	{
		setcolor(LIGHTGREEN);
		outtextxy(j+s,d+=s1 ,"Instructions");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"Instructions ");
	}
	if(b)//if b!=0  when function is called before the starting the game...
	{
		if(move==6)
		{
			setcolor(LIGHTGREEN);
			outtextxy(j+s,d+=s1 ,"Switch controller ");
		}
		else
		{
			setcolor(15);
			outtextxy(j,d+=s1 ,"Switch controller ");
		}
	}
	if(move==7)
	{
		setcolor(LIGHTGREEN);
		outtextxy(j+s,d+=s1 ,"Sounds ");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"Sounds ");
	}
	if(move==8)
	{
		setcolor(LIGHTGREEN);
		outtextxy(j+s,d+=s1 ,"Checker COLOR");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1 ,"Checker COLOR");
	}
	if(b)
	{
		if(move==9)
		{
			setcolor(LIGHTGREEN);
			outtextxy(j+s,d+=s1 ,"Credits ");
		}
		else
		{
			setcolor(15);
			outtextxy(j,d+=s1 ,"Credits ");
		}
	}
	if(move==10)
	{
		setcolor(LIGHTGREEN);
		outtextxy(j+s,d+=s1 ,"Exit ");
	}
	else
	{
		setcolor(15);
		outtextxy(j,d+=s1,"Exit ");
	}
	setcolor(15);

}
void Userdoc()//User documentation///
{
/*~~~~~~~~~~~~~~~~~~~~~~~~I*N*S*T*R*U*S*T*I*O*N*S~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	cleardevice();
	ifstream fin;
	fin.open("Userdoc.txt",ios::in);
	cout<<"\rUser Documentation";
	if(!fin)
	{
		gotoxy(1,1);
		cout<<"File corupt or.. not available.."
		    <<"\nPress any key to continue...";
		    getch();
		    return;

	}
	while(!fin.eof())
	{
		fin.getline(file,100,'\n');
		if(strcmp(file,"..")==0)
		{
			getch();
			cleardevice();
			gotoxy(1,1);
		}
		cout<<file<<"\n";
	}
	getch();
}

void sounds()//Enable or disable sounds...
{
	cleardevice();
	if(!fl)
		outtextxy(150,200,"Do you want to Enable sound?...[Enter]");
	else
		outtextxy(150,200,"Do you want to Disable sound?...[Enter]");
	key=bioskey(0);
	if(key==Enter && (!fl))
		fl=1;//fl controls the sound. if 1 plays sound
	else
		fl=0;
	cleardevice();
}
void getplname()//GEts player name///
{
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~P*L*A*Y*E*R**N*A*M*E~~~~~~~~~~~~~~~~~~~~~~~*/
	a=1;
	int l=1;
	cleardevice();
	while(a)
	{
		if(l)//If l!=0
		{
			gotoxy(33,11);
			cout<<"Give player 1 name...";
			rectangle(450,235,220,260);//Displays a box
			gotoxy(30,16);
			gets(::pl1);
		}
		if(strcmp(::pl1,'\0')==0)//if player has not entered any thing
			continue;//Again asks the name
				  //asks again & again till it recives a name
		else
			l=0;
		cleardevice();
		gotoxy(33,11);
		cout<<"Give player 2 name...";
		rectangle(450,235,220,260);//Displays a box
		gotoxy(30,16);
		gets(::pl2);
		if(strcmp(::pl2,'\0')!=0)
			a=0;

	}
	cleardevice();
	settextstyle(0,0,1);//Resettiing..text font
}

void drawcolor(int c,char c1[],char c2[],int p) //Drawing list of colors....
{
		int  i,j,l=1,cc=0;
		switch(p)
		{
			case 1:outtext(c1);break;//Printing the player name..
			case 2:outtext(c2);break;
		}
		for(j=80;j<170;j+=80)
		{
			for(i=70;i<600;i+=80,l++)
			{
				cc++;
				if(cc==c)
				{
					outtextxy(i-45,j,"->");//Pointing the color
					setfillstyle(1,l);
					fillellipse(i,j,25,25);
				}
				else
				{
					setfillstyle(1,l);
					fillellipse(i,j,25,25);

				}
			}
		}


}
void color()//NAvigation for choosing the checker color..
{
	int i,j,l,c=0;
	settextstyle(1,0,1);
	cleardevice();
	outtextxy(70,100,"   Default colours are pl1:-BLUE,pl2:-RED ");
	outtextxy(60,200,"   Do you want to choose the colours???? [Enter]");
	key=bioskey(0);
	if(key!=Enter)
		return;
	char c1[100],c2[100];
	strcpy(c1,pl1);
	strcpy(c2,pl2);
	strcat(c1," Choose the colour..Use Arrow keys to navigate[-> or <-]");
	strcat(c2," Choose the colour..Use Arrow keys to navigate[-> or <-]");
	for(j=1;j<=2;j++)
	{
		cleardevice();
		switch(j)
		{
			case 1:outtext(c1);break;
			case 2:outtext(c2);break;

		}
		drawcolor(c,c1,c2,j);
		for(;;)
		{
			key=bioskey(0);
			if(key==Enter)
			{
				if(j==1 && (c))
					cl1=c;
				else
					cl2=c;
				if(cl1==cl2)
				{
					gotoxy(30,16);
					cout<<"Cannot choose same colours...";
				}
				else
					break;

			}
			else if(key==Right_Arrow) /*right Cursor movement*/
			{
				c++;
				if(c==15)
					c=1;
				else if(c==0)
					c=14;
				cleardevice();
				drawcolor(c,c1,c2,j);
			}
			else if(key==Left_Arrow) /*left Cursor movement*/
			{
				c--;
				if(c==15)
					c=1;
				else if(c==0)
					c=14;
				cleardevice();
				drawcolor(c,c1,c2,j);
			}
			else if(key==ESC)
				break;

		}
	}
	settextstyle(0,0,1);
}
void cred()//Displaying the credits
{
	cleardevice();
	settextstyle(1,0,1);
	for(i=480;i>=0;i-=4)//To make it scroll from down to up...
	{
		key=0;
		cleardevice();
		settextstyle(4,0,5);
		setcolor(1);
		outtextxy(250,i,"Co");
		setcolor(2);
		outtextxy(300,i,"nn");
		setcolor(3);
		outtextxy(345,i,"ec");
		setcolor(4);
		outtextxy(380,i,"t");
		setcolor(5);
		outtextxy(395,i," 4");
		setcolor(10);
		settextstyle(1,0,1);
		outtextxy(250,i+50,"       v2.0");
		setcolor(1);
		outtextxy(0,i+70,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		setcolor(4);
		outtextxy(150,i+100,"2012-2013  Computer Science PROJECT K.V.I.I.T ");
		setcolor(14);
		outtextxy(250,i+150,"=>   CREDITS  <=");
		setcolor(2);
		outtextxy(250,i+200,"->  LEAD PROGRAMMER <-");
		setcolor(15);
		outtextxy(250,i+220,"-     [ Ashwin.R ]    -");
		setcolor(2);
		outtextxy(250,i+250,"  -> PROGRAMMERS <-");
		setcolor(15);
		outtextxy(250,i+280,"-   [ S.Vighnesh ]    -");
		outtextxy(250,i+300,"-   [ S.Preetham ]    -");
		outtextxy(250,i+320,"-   [ Satesh charan ] -");
		setcolor(1);
		outtextxy(0,i+340,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		setcolor(15);
		outtextxy(60,i+380,"->  Our Thanks to our TEACHER  Mr.Kamal Kishore Sharma...  <-");
		outtextxy(250,i+420,"-   THANK YOU !   -");
		delay(150);
		key=bioskey(1);
		if(key==Enter)
			break;
		sound(soun[random(7)]*4);

	}
	nosound();
	getch();

}
void circleno(void)
{
	int k=0,b[7][7]; /*First we create one more 2-D array to
					Get the index number where the numbers 1 or 2 should be stored.. */
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
			b[i][j]=++k; /*loop stores 1-49 all the values in
					   their increasing order.....*/
	for(i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			if(::circle_no==b[i][j])
			{
				if(connect[i][j]==0)
				{       if(controller==1)
						play++;

					if(::play%2!=0)/*.. '::play' which counts the number or plays..
							initially play=0; and when '::play' is odd
								means player 1, and for checking for odd or even we use ::play%2 */

						connect[i][j]=1;//PLAYER 1.
					else
						connect[i][j]=2;//PLAYER 1.
				 }
				 else
				 {
					sound(1500.0374);//Produces sound
					delay(800);
					nosound();
				 }
			}

		}
	}
}
void validmov(void)
{
	int c1[7][7],l=0;
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
			c1[i][j]=++l;//Stores 1-49///
	int i1,i2;
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
			if(::circle_no==c1[i][j])
			     i2=j;//Brings the colored circle to the bottom most
					//possible  blank circle

	for(i1=0;i1<7;i1++)
		 if(connect[i1][i2]==0)
		      ::circle_no=c1[i1][i2];

}
void st()// function to initialize variables
{
	play=circle_no=invalid=index1=index2=0;
	pl1[50]='\0',pl2[50]='\0';
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
			connect[i][j]=0;
		//7*7 matrix which contains all the 49 circle information
	getplname();
}

void title()
{
/*~~~~~~~~~~~~~~~~~~~~~~~~T*I*T*L*E~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int a;
	int i,j,k,m;
	double kk=0;
	for(i=480,j=0,k=640,m=640;m!=200;)
	{
		cleardevice();
		if(j<150)
			j+=6;
		if(i>153)
			i-=8;
		if(k>298)
			k-=8;
		if(m>200)
			m-=8;
			//To bring the letters from each direction,,,.
		settextstyle(4,0,5);
		setcolor(1);
		outtextxy(200,j,"Co");
		setcolor(2);
		outtextxy(250,i,"nn");
		setcolor(3);
		outtextxy(k,150,"ec");
		setcolor(4);
		outtextxy(330,i,"t");
		setcolor(5);
		outtextxy(340,j," 4");
		setcolor(10);
		settextstyle(1,0,1);
		outtextxy(m,250,"       v2.0");
		sound(kk);//Sound...
		       kk+=5.302938;//Changing the frequency..
		delay(80);
		nosound();

	}
	nosound();
	rectangle(560,380,80,400);
	for(i=80,j=150,a=0;i<580;i+=20,a++)
	{
		outtextxy(250,375,"Game Loading...");  //shows Game Loading inside a  rectangle which
		bar(i,380,j,400);//loading Animation
		j=i;		// is continuously filed by bars
				//   & diffrent width with some delay time.
		sound( soun[random(7)] * 4 );
			//Random function used to select random
			//sound frequencies from the array 'soun'
		delay(300);
	}
	nosound();
	setcolor(13);
	settextstyle(4,0,1);
	outtextxy(90,300,"Press Any key to continue");
	getch();

}
int result(void)/* Checks the result...*/
{
	int c=0,k;
//~~~~~~~~~~~~~~~~~~~~~~/*Check for rows*/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for(i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			if(connect[i][j])
			{
				if(connect[i][j]==connect[i][j+1])
				{
					if(connect[i][j]==connect[i][j+2])
/*Check for rows*/					{
						if(connect[i][j]==connect[i][j+3])
						{
							if(connect[i][j]==1)
							{
								c=1;
								return c;
							}
							else if(connect[i][j]==2)
							{
								c=2;
								return c;
							}
						}
					}
				}
			}
//~~~~~~~~~~~~~~~~~~~~~~~~~/*Check for column*//*~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if(connect[j][i])
			{
				if(connect[j][i]==connect[j+1][i])
				{
					if(connect[j][i]==connect[j+2][i])
					{
						if(connect[j][i]==connect[j+3][i])
/*Check for column*/						{
							if(connect[j][i]==1)
							{
								c=1;
								return c;
							}
							else if(connect[j][i]==2)
							{
								c=2;
								return c;
							}
						}
					}
				}
			}
		}
	}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~/*Check for Main diagonals*/~~~~~~~~~~~~~~~~
	for(i=0;i<4;i++)
	{
		if(connect[i][i])
		{
			if(connect[i][i]==connect[i+1][i+1])
			{
				if(connect[i][i]==connect[i+2][i+2])
				{
					if(connect[i][i]==connect[i+3][i+3])
/*Check for Main diagonal 1*/		{
						if(connect[i][i]==1)
						{
							c=1;
							return c;
						}
						else if(connect[i][i]==2)
						{
							c=2;
							return c;
						}
					}
				}
			}
		}
	}
	for(i=0,j=6;j>=3;j--,i++)
	{
		if(connect[i][j])
		{
			if(connect[i][j]==connect[i+1][j-1])
			{
				if(connect[i][j]==connect[i+2][j-2])
				{
					if(connect[i][j]==connect[i+3][j-3])
					{
						if(connect[i][j]==1)
/*Check for Main diagonal 2*/			{
							c=1;
							return c;
						}
						else if(connect[i][j]==2)
						{
							c=2;
							return c;
						}
					}
				}
			}
		}
	}
//~~~~~~~~~~~~~~~~~~~~/*Check for Left-Right diagonal*/~~~~~~~~~~~~~~
	for(i=0;i<3;i++)
	{
		for(j=3;j>i;j--)
		{
			if(connect[i][j])
			{
				if(connect[i][j]==connect[i+1][j+1])
				{
					if(connect[i][j]==connect[i+2][j+2])
					{
						if(connect[i][j]==connect[i+3][j+3])
						{
							if(connect[i][j]==1)
/*Check for top Left-Right diagonal*/							{
								c=1;
								return c;
							}
							else if(connect[i][j]==2)
							{
								c=2;
								return c;
							}
						}
					}
				}
			}
			else if(connect[j][i])
			{
				if(connect[j][i]==connect[j+1][i+1])
				{
					if(connect[j][i]==connect[j+2][i+2])
					{
						if(connect[j][i]==connect[j+3][i+3])
						{
							if(connect[j][i]==1)
							{
								c=1;
								return c;
							}
							else if(connect[j][i]==2)
							{
								c=2;
								return c;
							}
						}
					}
				}
			}
		}
	}
//~~~~~~~~~~~~~~~~~~~~~Check for Right- Left diagonal~~~~~~~~~~~~~~~~
	for(i=0;i<3;i++)
	{
		for(j=3;j<6-i;j++)
		{
			if(connect[i][j])
			{
				if(connect[i][j]==connect[i+1][j-1])
				{
					if(connect[i][j]==connect[i+2][j-2])
					{
/*Check for top Right- Left diagonal up*/	if(connect[i][j]==connect[i+3][j-3])
						{
							if(connect[i][j]==1)
							{
								c=1;
								return c;
							}
							else if(connect[i][j]==2)
							{
								c=2;
								return c;
							}
						}
					}
				}
			}
		}
	}
	for(i=6,k=0;k<3;i--,k++)
	{
		for(j=3;j>k;j--)
		{
			if(connect[i][j])
			{
				if(connect[i][j]==connect[i-1][j+1])
				{
					if(connect[i][j]==connect[i-2][j+2])
					{
/*Check for top Right- Left diagonal dw*/	if(connect[i][j]==connect[i-3][j+3])
						{
							if(connect[i][j]==1)
							{
								c=1;
								return c;
							}
							else if(connect[i][j]==2)
							{
								c=2;
								return c;
							}
						}
					}
				}
			}
		}
	}

	return c;
}

/*-----------------------------------------------------------------------------
		RESULT .....!!!
--------------------------------------------------------------------------------*/
void end(int re)//Declaring the result....
{
	settextstyle(1,0,1);
	strcat(pl1,"....you won the game");//Copying the string...
	strcat(pl2,"....you won the game");
	gotoxy(1,1);
	if(re==1)
		cout<<pl1<<"               ";
	else if(re==2)
		cout<<pl2<<"                  ";
	else if(re==0)
		cout<<"The game is draw....                ";
	getch();
	main(0);//calls the main function...
}
void showsav()//Shows the files saved in the
{
	char file[15];
	cleardevice();
	int counter=0;
	fstream fin;
	fin.open("save.txt",ios::in|ios::out);//reads the textfile

	if(!fin)
	{
		cout<<"\nNo Saved files found....\n";
		cout<<"Press any key to continue....\n";
		getch();
		return;
	}
	gotoxy(1,1);
	cout<<"\r\t\tList of Saved games.....\n\n\n";
	while(!fin.eof())
	{
		counter++;
		fin.getline(file,15,'\n');
		if(strcmp(file,'\0')!=0)
			cout<<"\t\t\t->"<<file<<"\n";
		if(counter==20)
		{
			cout<<"\n\tPress any key to goto next Page...\n";
			getch();
			cleardevice();
			gotoxy(1,1);
			cout<<"\r\t\tList of Saved games.....\n\n\n";
			counter=0;
		}

	}
	cout<<"\n\t\t~~ END ~~";
	getch();
	cleardevice();
}
class save//class containing
{	       // game information
	public:
		char name1[50];
		char name2[50];
		int conn[7][7];
		int plays;
		int col1;
		int col2;
		save()//constructor.. of class save...
		{     //stores the progress of the gamee1,pl1);
			for(i=0;i<7;i++)
				for(j=0;j<7;j++)
					conn[i][j]=connect[i][j];//copying the 7*7 array..
			strcpy(name1,pl1);
			strcpy(name2,pl2);
			plays=play;
			col1=cl1;
			col2=cl2;          //copying variables///
		}
};
int gamesave()//saves game to file...
{
	char str[30];
	save c;/// object of class save....
	int fl=0;
	cleardevice();
	outtextxy(100,200,"Do you want to Save and Quit the game...???[Enter]");
	key=bioskey(0);
	if(key==Enter)
	{
		while(1)
		{
			ofstream fileout,fout,chk;// ofstream variables//
			cleardevice();
			textcolor(9);
			gotoxy(1,1);
			cout<<"\n\n\n\n\n\n\n";
			cout<<"\t\t\tGive file name to be saved in TC\\bin\\...";
			cout<<"\n\t\t\tWarning... REMEMBER THE FILE NAME SO \n";
			cout<<"\t\t\tTHAT YOU CAN OPEN IT NEXT TIME!....\n";
			rectangle(450,235,220,260);//rectangle box..
			gotoxy(30,16);
			cin>>str;
			strcat(str,".dat");
			chk.open(str,ios::nocreate);//checking if file already exist..?
			if(chk)
			{
				gotoxy(30,18);
				cout<<"File already exists....";
				cout<<"\n\t\tDo you want to replace the excisting file..?[Enter]";
				key=bioskey(0);
				if(key==Enter)
					fl=1;
			}
			else
				fl=1;
			if(fl)//if not...
			{//save the game...
				fileout.open(str,ios::in|ios::binary);
				fileout.write((char*)&c,sizeof(c));
				fout.open("save.txt",ios::app);
				fout<<str<<"\n";//save the name of the file in another file..
				cout<<"\n\n\t\t\t\tWRITE SUCESSFUL.....";
				fileout.close();
				getch();
				break;
			}
		}

	}
	else
		return 0;
}
void remov()////deleting a saved file...
{
	char str[10],f[20];
	fstream fdel,ftemp,fop;
	int del=0;
	cleardevice();
	gotoxy(1,1);
	settextstyle(1,0,1);
	outtextxy(100,200,"Do you want to Delete a Previously saved game[Enter]??");
	key=bioskey(0);
	if(key==Enter)
	{
		cleardevice();
		save c;
		outtextxy(150,200,"Give the file name you want to Delete!...");
		rectangle(450,235,220,260);
		gotoxy(30,16);
		cin>>str;
		strcat(str,".dat");
		fop.open(str,ios::in);
		if(!fop)
		{
			cout<<"\n\n\t\t\t\tFile Not found.....\n	";
			cout<<"\t\t\tPress any key to continue...";
			getch();
			return;
		}
		remove(str);
		fdel.open("save.txt",ios::in);
		ftemp.open("temp.txt",ios::out);
		while(!fdel.eof())
		{
			fdel.getline(f,20,'\n');
			if(strcmp(f,str)!=0)
				ftemp<<f<<"\n";

		}
		remove("save.txt");
		rename("temp.txt","save.txt");
		cout<<"\n\t\t\t\tDelete Sucessful....";
		getch();
	}
	settextstyle(0,0,1);
	cleardevice();
}
void opensave()//opening a saved file
{
	char str[30];
	cleardevice();
	gotoxy(1,1);
	settextstyle(1,0,1);
	outtextxy(100,200,"Do you want to Open a Previously saved game[Enter]??");
	key=bioskey(0);
	if(key==Enter)
	{
		cleardevice();
		save c;
		outtextxy(150,200,"Give the file name you want to Open!...");
		rectangle(450,235,220,260);
		gotoxy(30,16);
		cin>>str;
		strcat(str,".dat");
		ifstream filein;
		filein.open(str,ios::out|ios::binary);
		filein.read((char*)&c,sizeof(c));
		if(!filein)
		{
			cout<<"\n\nNO SAVES FOUND!!!\n";
			cout<<"\nPlease Start a new game..";
			settextstyle(0,0,1);
			getch();
			main(0);
		}
		else
		{
				     //restoring variables
			play=c.plays;
			circle_no=invalid=index1=index2=0;
			cl1=c.col1,cl2=c.col2;
			for(i=0;i<7;i++)
				for(j=0;j<7;j++)
					connect[i][j]=c.conn[i][j];
			strcpy(pl1,c.name1);
			strcpy(pl2,c.name2);
			cout<<"\n\n\t\t LOAD SUCESSFUL...";
			cout<<"\n\t\tPress any key to continue...!";
			getch();
		}
	}
	settextstyle(0,0,1);
	cleardevice();
	drawcircle(2.0);//starting the game
}
