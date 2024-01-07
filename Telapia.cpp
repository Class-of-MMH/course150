#include <stdio.h>
#include<iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include<math.h>
#include <thread>
#include<mmsystem.h>
using namespace std;

//variables
COORD coord = {0, 0}; // sets coordinates to 0,0
bool endGame=false;
bool bullet=false;
bool thas=false;
bool thas2=false;
bool thas3=false;
int bullet_Y=1;
int x1_bullet_x,x1_bullet_Y,x2_bullet_x,x2_bullet_Y,x3_bullet_x,x3_bullet_Y,boom=0;
int ciclos=0;
int bullet_X=0;
int score=0;
int k=0;
int health=100;
bool shooting=false;
int v1,v2,tui,boom2,boom3;

    void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // setting the X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

    void fire() {
    // Specify the file name directly in the PlaySound function
    PlaySound(TEXT("fire.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
      void playMusic() {
    // Specify the file name directly in the PlaySound function
    PlaySound(TEXT("Suzume.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

    void textcolor (int iColor)//function to generate color
{
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
/*
       0- black
        1- blue
        2- green
        3- cyan
        4- red
        5- purple
        6- yellow
        7- white
        8- gray
        9- light blue
*/
}

    struct my_ship
{
    // structure of my_ship- the spaceships
    int posX=25, posY=23, shoot;

}my_ship,x1,x2,x3;

    void border()
{

    //creates the border
    textcolor(9);
    int i=0;
    for(i=2;i<50;i++)
    { //horizontal 2 lines
        gotoxy(i,2);
        printf("%c",176);
        gotoxy(i,25);
        printf("%c",176);
    }

    for(i=2;i<=25;i++)
    { //vertical 2 lines
        gotoxy(2,i);
        printf("%c",176);
        gotoxy(50,i);
        printf("%c",176);
    }
    textcolor(7);
}

void drawship()
{
    textcolor(2); // changes the color
    // draws our spaceship
    gotoxy(my_ship.posX-1,my_ship.posY);
    printf("%c",219);
    gotoxy(my_ship.posX+1,my_ship.posY);
    printf("%c",219);
    gotoxy(my_ship.posX,my_ship.posY);
    printf("%c",206);
    gotoxy(my_ship.posX,my_ship.posY-1);
    printf("%c",'A');

    textcolor(7); // sets the color to white

}
void draw_enemy()
{
    //3 enemy ships
    textcolor(4);
    gotoxy(x1.posX-1,x1.posY);
    printf("%c",219);
    gotoxy(x1.posX+1,x1.posY);
    printf("%c",219);
    gotoxy(x1.posX,x1.posY);
    printf("%c",206);
    gotoxy(x1.posX,x1.posY+1);
    printf("%c",'V');


    gotoxy(x2.posX-1,x2.posY);
    printf("%c",219);
    gotoxy(x2.posX+1,x2.posY);
    printf("%c",219);
    gotoxy(x2.posX,x2.posY);
    printf("%c",206);
    gotoxy(x2.posX,x2.posY+1);
    printf("%c",'V');

    gotoxy(x3.posX-1,x3.posY);
    printf("%c",219);
    gotoxy(x3.posX+1,x3.posY);
    printf("%c",219);
    gotoxy(x3.posX,x3.posY);
    printf("%c",206);
    gotoxy(x3.posX,x3.posY+1);
    printf("%c",'V');

    textcolor(7);

}


void Enemy_movement()
{

    // calculates a random movement for the enemies
    srand(time(0)); // to get real random numbers
    int dir;

    dir=rand()%4;
    switch(dir)
    {
        case 0: if(x1.posX<48)  {  x1.posX++; } break;
        case 1: if(x1.posX>4)   {  x1.posX--; } break;
        case 2: if(x1.posY<22)  {  x1.posY++; } break;
        case 3: if(x1.posY>4)   {  x1.posY--; } break;

        //The conditions here are to keep the ships in the block

    }

    dir=rand()%4;
    switch(dir)
    {
        case 0: if(x2.posX<48) {  x2.posX++; } break;
        case 1: if(x2.posX>4)  {  x2.posX--; } break;
        case 2: if(x2.posY<22) {  x2.posY++; } break;
        case 3: if(x2.posY>4)  {  x2.posY--; } break;

    }
    dir=rand()%4;
    switch(dir)
    {
        case 0: if(x3.posX<48) {  x3.posX++; } break;
        case 1: if(x3.posX>4)  {  x3.posX--; } break;
        case 2: if(x3.posY<22) {  x3.posY++; } break;
        case 3: if(x3.posY>4)  {  x3.posY--; } break;

    }
}

void printPanel()
{
    //  Print information
    gotoxy(52,5);
    printf("\t  _-_");
    gotoxy(52,6);
    printf("TELAPIA UNIVERSE");
    gotoxy(52,7);
    printf("\t  -_-");
    gotoxy(52,10); //these are just the co-ordinates where infos gonna be printed
    printf("ESC - exit");
    gotoxy(52,11);
    printf("W,A,S,D-move");
    gotoxy(52,12);
    printf("Space- shoot");
    gotoxy(52,13);
    printf("Shoots %d", my_ship.shoot);
    gotoxy(52,16);
    printf("Health %d %%",health);
   // printf("Gametime %d boom %d", ciclos,boom);
    gotoxy(52,14);
    printf("Score: %d",score);

}
void controller()
{
    char x;
    if(kbhit())
    {
        x=getch();
    }

    switch(x)
    {
        case 'a': if(my_ship.posX>4)  { my_ship.posX--; } break;
        case 's': if(my_ship.posY<24) { my_ship.posY++; } break;
        case 'd': if(my_ship.posX<48) { my_ship.posX++; } break;
        case 'w': if(my_ship.posY>4)  { my_ship.posY--; } break;
        case 32:  {my_ship.shoot++; bullet=true; shooting=true;k=1;  } break; //spacebar
        case 27: { printPanel(); gotoxy(2,15); printf("\t\t    GAME OVER"); gotoxy(2,26); thread musicThread(playMusic);
               musicThread.join();
               Sleep(12000); exit(0); endGame=true; } break;        //esc
    }

}

void Shooting()
{

    // function that creates the shoot of the player
    if(bullet==true)
    {
        if(shooting==true) { bullet_X=my_ship.posX; shooting=false;}
        bullet_Y++;
        gotoxy(bullet_X,my_ship.posY-bullet_Y); //y will change everytime; this will make the bullet move
        textcolor(6);
        printf("A");
        textcolor(7);
    }
    if((bullet_Y>1)&&((abs(bullet_X-x1.posX)<=1 && my_ship.posY-bullet_Y==x1.posY) || (abs(bullet_X-x2.posX)<=1 && my_ship.posY-bullet_Y==x2.posY) || (abs(bullet_X-x3.posX)<=1 && my_ship.posY-bullet_Y==x3.posY)) ){
        {
            score+=50;
            printPanel();
            gotoxy(bullet_X-3,23-bullet_Y);
            textcolor(2);
            printf("BOOM 50+");


          //  Sleep(2000);
        bullet=false;
        bullet_Y=1;
        shooting=false;
    }
    }
    if(my_ship.posY-bullet_Y<4) // bullet will disappear when reached top
    {
        bullet=false;
        bullet_Y=1;
        shooting=false;
    }
}

void initializePosition()
{

    // initialize the positions
    my_ship.posX=25;
    my_ship.posY=23;
    x1.posX=25;
    x1.posY=10;
    x2.posX=30;
    x2.posY=7;
    x3.posX=6;
    x3.posY=4;
}


void Enemy_Shooting()
{

    // function that creates the shoot of the player


    if(boom!=0){


            if(boom==7){


        if(thas==true) {

        x1_bullet_x=x1.posX;
        thas=false;
       }

        x1_bullet_Y++;
        gotoxy(x1_bullet_x,x1.posY+x1_bullet_Y); //initial shooting pos
        textcolor(6);
        printf("V");


       // Sleep(110);
        textcolor(7);
    }
    else boom=0;}
    if(((abs(x1_bullet_x-my_ship.posX)<=1 && x1.posY+x1_bullet_Y==my_ship.posY)))
        {
            score-=30;
            health-=25;
            if(health==0){ gotoxy(8,13); textcolor(1); printf("<<--Remember, We only live once-->>"); printPanel(); gotoxy(2,15); printf("\t\t    GAME OVER");thread musicThread(playMusic);
               musicThread.join();
               Sleep(12000); gotoxy(2,26); exit(0); endGame=true; }
            gotoxy(my_ship.posX+3,my_ship.posY);
        textcolor(4);
        printf("-30");

        boom=0;
        x1_bullet_Y=1;
        thas=false;
    }

    if(x1.posY+x1_bullet_Y>23) // bullet will disappear when reached bottom
    {
        boom=0;
        x1_bullet_Y=1;
        thas=false;
    }
}

void Enemy_Shooting2()
{

    // function that creates the shoot of the player


    if(boom2!=0){


            if(boom2==11){


        if(thas2==true) {

        x2_bullet_x=x2.posX;
        thas2=false;
       }

        x2_bullet_Y++;
        gotoxy(x2_bullet_x,x2.posY+x2_bullet_Y); //initial shooting pos
        textcolor(6);
        printf("V");
        textcolor(7);
    }
    else boom2=0;}
    if(((abs(x2_bullet_x-my_ship.posX)<=1 && x2.posY+x2_bullet_Y==my_ship.posY)))
        {
            score-=30;
            health-=25;
            if(health==0){ gotoxy(8,13); textcolor(1); printf("<<--Remember, We only live once-->>"); printPanel(); gotoxy(2,15); printf("\t\t    GAME OVER");thread musicThread(playMusic);
               musicThread.join();
               Sleep(12000); gotoxy(2,26); exit(0); endGame=true; }
            gotoxy(my_ship.posX+3,my_ship.posY);
        textcolor(4);
        printf("-30");

        boom2=0;
        x2_bullet_Y=1;
        thas2=false;
    }

    if(x2.posY+x2_bullet_Y>23) // bullet will disappear when reached bottom
    {
        boom2=0;
        x2_bullet_Y=1;
        thas2=false;
    }
}

void Enemy_Shooting3()
{

   if(boom3!=0){
            if(boom3==13){

            if(thas3==true) {
            x3_bullet_x=x3.posX;
            thas3=false;
                }

        x3_bullet_Y++;
        gotoxy(x3_bullet_x,x3.posY+x3_bullet_Y); //initial shooting pos
        textcolor(6);
        printf("V");
        textcolor(7);
    }

    else boom3=0;}
    if(((abs(x3_bullet_x-my_ship.posX)<=1 && x3.posY+x3_bullet_Y==my_ship.posY)))
        {
            score-=30;
            health-=25;
            if(health==0){ gotoxy(8,13); textcolor(1); printf("<<--Remember, We only live once-->>"); printPanel(); gotoxy(2,15); printf("\t\t    GAME OVER");thread musicThread(playMusic);
               musicThread.join();
               Sleep(12000); gotoxy(2,26); exit(0); endGame=true; }
            gotoxy(my_ship.posX+3,my_ship.posY);
        textcolor(4);
        printf("-30");

        boom3=0;
        x3_bullet_Y=1;
        thas3=false;
    }

    if(x3.posY+x3_bullet_Y>23) // bullet will disappear when reached bottom
    {
        boom3=0;
        x3_bullet_Y=1;
        thas3=false;
    }
}



int main()
{
    system("mode 65,28");
    system("title Telapia Spaceship Shooter");
    initializePosition();
    border();
        drawship();      //draws our spaceship
        draw_enemy();
    score=0;
    gotoxy(52,10); textcolor(9); printf("LIFE IS ONLY PRECIOUS CAUSE ITS GONNA END SOMEDAY");gotoxy(52,12); printf("SO JUST HIT 'Y'/'y' AND PRESS ENTER :");
        char pick;
             gotoxy(52,13);
               cin>>pick;
               Sleep(100);

   if(pick=='y' ||pick=='Y'){ while(endGame==false)
    {


        int p=10;
       if((score/250)<9) p=10-(score/250);

        if(ciclos%p==0)// its a loop that will make the enemy ships spawn ein every 10 mili seconds

        {
                Enemy_movement();
        }
        border();
        drawship();      //draws our spaceship
        draw_enemy();  //draws the enemies
        Shooting();

        if(boom==0) {boom=rand()%13;
                    if(boom!=0) {
                            thas=true;
                        }

        }
        Enemy_Shooting();


        if(boom2==0) {boom2=rand()%19;
                    if(boom2!=0) {
                            thas2=true;
                        }

        }
        Enemy_Shooting2();

        if(boom3==0) {boom3=rand()%37;
                    if(boom3!=0) {
                            thas3=true;
                        }

        }
        Enemy_Shooting3();

        controller();   // checks if key is pressed
        printPanel();
        Sleep(40);  // pauses excecution for 40 miliseconds

        system("cls"); // clears the screen

      if(k==1){
            {thread fireThread(fire);
                k=0;
                    fireThread.join();
                    }
      }
        ciclos++;
        }
   }



    return 0;
}
