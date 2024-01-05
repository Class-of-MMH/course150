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
int bullet_Y=1;
int ciclos=0;
int bullet_X=0;
int score=0;
int k=0;
bool shooting=false;

    void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // setting the X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
    void playMusic() {
    // Specify the file name directly in the PlaySound function
    PlaySound(TEXT("Suzume.wav"), NULL, SND_FILENAME | SND_ASYNC);

}
    void fire() {
    // Specify the file name directly in the PlaySound function
    PlaySound(TEXT("fire.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
        case 27: { gotoxy(2,26); exit(0); endGame=true; } break;        //esc
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
    gotoxy(52,14);
   // printf("Gametime %d", ciclos);
   // gotoxy(52,15);
    printf("Score: %d",score);

}

void Shooting()
{

    // function that creates the shoot of the player
    if(bullet==true)
    {
        if(shooting==true) { bullet_X=my_ship.posX; shooting=false;}
        bullet_Y++;
        gotoxy(bullet_X,my_ship.posY-bullet_Y); //initial shooting pos
        textcolor(6);
        printf("A");
        textcolor(7);
    }
    if((bullet_Y>1)&&((abs(bullet_X-x1.posX)<=1 && bullet_Y==23-x1.posY) || (abs(bullet_X-x2.posX)<=1 && bullet_Y==23-x2.posY) || (abs(bullet_X-x3.posX)<=1 && bullet_Y==23-x3.posY)) ){
        {
            score+=50;
            printPanel();
            gotoxy(bullet_X-4,23-bullet_Y);

            int x=rand()%3;
    switch(x)
    {
        case 0:printf("Uff boddo legeche"); break;
        case 1:printf("Thaaaaas"); break;
        case 2:printf("Uri Baba"); break;

    }

            Sleep(2000);
        bullet=false;
        bullet_Y=1;
        shooting=false;
    }
    }
    if(bullet_Y>18) // bullet will disappear when reached top
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

int main()
{
    system("mode 65,28");
    system("title Telapia Spaceship Shooter");
    initializePosition();
    score=0;


    while(endGame==false)
    {

        int p=10;
       if(p>2) p=10-(score/250);

        if(ciclos%p==0)// its a loop that will make the enemy ships spawn ein every 10 timeunits
        {
                Enemy_movement();
        }
        border();
      drawship();      //draws our spaceship
        draw_enemy();  //draws the enemies
        Shooting();
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
       // if((ciclos+score)%200==0) {
        //        thread musicThread(playMusic);
       //         musicThread.join();
     // }

    ciclos++;


        }


    return 0;
}
