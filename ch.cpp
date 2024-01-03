
void Enemy_Shooting()
{

    // function that creates the shoot of the player
    int v1,v2,tui;
    tui=rand()%3;
    switch(tui){

        case 0: v1=x1.posX; v2=x1.posY;
        case 1: v1=x2.posX; v2=x2.posY;
        case 3; v1=x3.posX; v2=x3.posY;
    }

    if(boom!=0){
            if(boom==7){

        if(thas==true) {

        x2_bullet_x=v1;
      //  x2_bullet_Y=v2;
        thas=false;
       }
       Sleep(20);
        x2_bullet_Y++;
        gotoxy(x2_bullet_x,v2+x2_bullet_Y); //initial shooting pos
        textcolor(6);
        printf("V");
        textcolor(7);
    }
    else boom=0;}
    if(((abs(x2_bullet_x-my_ship.posX)<=1 && v2+x2_bullet_Y==my_ship.posY)))
                            //|| (abs(x2_bullet_x-x2.posX)<=1 && x2_bullet_Y==23-v2) || (abs(x2_bullet_x-x3.posX)<=1 && x2_bullet_Y==23-x3.posY)) ){
        {
            score-=30;
           // printPanel();
            //gotoxy(x2_bullet_x-3,23-x2_bullet_Y);
            //printf("BOOM 50+");

        boom=0;
        x2_bullet_Y=1;
        thas=false;
    }

    if(v2+x2_bullet_Y>23) // bullet will disappear when reached bottom
    {
        boom=0;
        x2_bullet_Y=1;
        thas=false;
    }
}
