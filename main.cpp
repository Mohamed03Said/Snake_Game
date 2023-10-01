#include"graphics.h"
#include<climits>
#include<queue>
#include <stdio.h>

using namespace std;

const int EMPTY    = 0;
const int BODY     = 1;
const int APPLE    = 2;
const int WALL     = 3;
const int REDAPPLE = 4;
const int PANANA   = 5;

int score = 0;
char arr[10000];

enum Directions {UP,DOWN,LEFT,RIGHT};
Directions snakeDirection = DOWN;
bool isgameover = false;

struct location
{
    int r;
    int c;
};
bool FireStarted;
location fireLocation;
Directions fireDirection;
queue<location> SnakeBody;

int board[36][35] =
{
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

//the graph
void checkkeyinput()
{
    char clo;
    if(kbhit())
    {
        clo = getch();
        if(clo == 0)
        {
            clo = getch();
        }
    }
}
void gametrack(){
    string sound = "Snake Music.wav";
 PlaySound(sound.c_str(),NULL,SND_ASYNC);
}
void DStart()
{
    //gametrack();
    initwindow(630,630);
    setcolor(WHITE);
    settextstyle(6,0,2);
    outtextxy(240,30,"Welcome to");
    setcolor(COLOR(255,0,0));
    settextstyle(6,0,4.5);
    //readimagefile("apple.ico",50,50,100,100);
    outtextxy(175,70,"* Snake Game *");
    setcolor(WHITE);
    settextstyle(8,0,2);
    outtextxy(50,150,"Created By :");
    setcolor(LIGHTMAGENTA);
    settextstyle(6,0,5);
    outtextxy(50,190,"Mohamed Samir");
    setcolor(LIGHTMAGENTA);
    settextstyle(6,0,5);
    outtextxy(50,290,"Mohamed Said");
    setcolor(LIGHTMAGENTA);
    settextstyle(6,0,5);
    outtextxy(50,390,"Mohamed Hussien");
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(6,0,2);
    outtextxy(125,550,"Press Enter To Start The Game" );
    checkkeyinput();
    while(!kbhit());
    closegraph();
}

void eraseFire(int r, int c)//remove the tail of fire
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, BLACK);//make background black
    bar(x, y, x + 18, y + 18);
}
void drawFire(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, LIGHTCYAN);
    readimagefile("fire.ico",x+3,y+3,x+15,y+15);
    //bar( x +3, y +3, x +15, y +15);
}
void eraseSnakeBody(int r, int c)//remove the tail of snake
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, BLACK);
    bar(x, y, x + 18, y + 18);
}
void eatvoise(){
string sound = "apple-crunch.wav";
PlaySound(sound.c_str(),NULL,SND_ASYNC);
}

void drawSnakeBody(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, LIGHTMAGENTA);
    bar( x +2, y +2, x +16, y +16);//to dosn't take all pixels
}

void drawSnakegreenBody(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, MAGENTA);
    bar( x, y, x +18, y +18);
}
void drawSnakeredBody(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, MAGENTA);
    bar( x, y, x +18, y +18);
}
void drawSnakeyellowBody(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    setfillstyle(SOLID_FILL, MAGENTA);
    bar( x, y, x +18, y +18);
}
void drawApple(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    readimagefile("apple.ico",x+1,y+1,x+16,y+16);
}
void drawRedApple(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    readimagefile("redapple.ico",x+1,y+1,x+17,y+17);
}

void drawPanana(int r, int c)
{
    int x = c * 18;
    int y = r * 18;

    readimagefile("banana.ico",x,y,x+18,y+18);
}


void drawWall(int r, int c)
{
    int x = c * 18;
    int y = r * 18;
    setfillstyle(SOLID_FILL, MAGENTA);
    bar( x, y, x +18, y +18);

    setcolor(LIGHTMAGENTA);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    line(x+0,y+0,x+18,y+0);
    line(x+0,y+9,x+18,y+9);
    line(x+0,y+18,x+18,y+18);

    line(x+12,y+0,x+12,y+9);
    line(x+6,y+9,x+6,y+18);

}
void drawBoard()
{
    for(int r = 0; r < 36; r++)
        for(int c = 0; c < 35; c++)
            switch(board[r][c])
            {
            case EMPTY:
                break;
            case BODY:
                drawSnakeBody(r,c);
                break;
            case APPLE:
                drawApple(r,c);
                break;
            /*case REDAPPLE:
                drawRedApple(r,c);
                break;
                case PANANA:
                drawPanana(r,c);
                break;*/
            case WALL:
                drawWall(r,c);
                break;
            }
  ///  setcolor(WHITE);
    //outtextxy(20,1,"Score:0");
}

void initSnake()
{
    location loc;
    loc.r = 2;
    loc.c = 10;
    for(int i=0; i<=2; i++)
    {
        SnakeBody.push(loc);
        board[loc.r][loc.c] =1;
        loc.r +=1;
    }
}
location getNextFireLocation()
{
    location nextFireLoc = fireLocation;
    switch(fireDirection)
    {
    case UP:
        nextFireLoc.r -= 1;
        break;
    case DOWN:
        nextFireLoc.r += 1;
        break;
    case LEFT:
        nextFireLoc.c -= 1;
        break;
    case RIGHT:
        nextFireLoc.c += 1;
        break;
    }
    return nextFireLoc;

}
location getnexthead()
{
    location head = SnakeBody.back();
    switch(snakeDirection)
    {
    case UP:
        head.r -= 1;
        break;
    case DOWN:
        head.r += 1;
        break;
    case LEFT:
        head.c -= 1;
        break;
    case RIGHT:
        head.c += 1;
        break;
    }
    return head;
}

/*void counterscore()
{
    setcolor(WHITE);
    //settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    sprintf(arr,"Score : %d",score);
    outtextxy(20,0,arr);
}
*/
void generatenextapple()
{
    int r,c;
    do
    {
        r = rand()%32+1;
        c = rand()%35;
    }
    while(board[r][c] != EMPTY);
    score++;
    board[r][c] = APPLE;
    drawApple(r,c);
    // score++;
    // score++ ;
    /* string s = to_string(score);
     int y;
     if (s.size()<2)
      y = 6;
     else
      y = 7;
    char Score[s.size()+y] = "Score: ";
    for (int i = 6 ; i < s.size()+y ; i++)
      Score[i]= s[i-y];
    outtextxy(2,1,Score); */
}
void scoreshownn()
{
    setcolor(LIGHTCYAN);
    sprintf(arr,"Score : %d",score);
    outtextxy(300,100,arr);
}
void scoreshown()
{
    setcolor(WHITE);
    sprintf(arr,"Score : %d",score);
    outtextxy(20,1,arr);
}

void generatenextredapple()
{
    int r,c;
    do
    {
        r = rand()%32+1;
        c = rand()%35;
    }
    while(board[r][c] != EMPTY);
    score++;
    board[r][c] = REDAPPLE;
    drawRedApple(r,c);
    // score++;
}
void generatenextbanana()
{
    int r,c;
    do
    {
        r = rand()%32+1;
        c = rand()%35;
    }
    while(board[r][c] != EMPTY);
    score++;
    board[r][c] = PANANA;
    drawPanana(r,c);
    // score++;
}

void  moveSnaketonextlocation(location nexthead)
{
    SnakeBody.push(nexthead);
    drawSnakeBody(nexthead.r,nexthead.c);
    board[nexthead.r][nexthead.c] = 1;

    location tail = SnakeBody.front();
    SnakeBody.pop();
    eraseSnakeBody(tail.r,tail.c);
    board[tail.r][tail.c] = 0;
}
void moveandgrawsnake(location nexthead)
{
    SnakeBody.push(nexthead);
    drawSnakeBody(nexthead.r,nexthead.c);
    board[nexthead.r][nexthead.c] = 1;

}
void moveandgrawgreensnake(location nexthead)
{
    SnakeBody.push(nexthead);
    drawSnakegreenBody(nexthead.r,nexthead.c);
    board[nexthead.r][nexthead.c] = 1;
}
void moveandgrawredsnake(location nexthead)
{
    SnakeBody.push(nexthead);
    drawSnakeredBody(nexthead.r,nexthead.c);
    board[nexthead.r][nexthead.c] = 1;
}
void moveandgrawyellowsnake(location nexthead)
{
    SnakeBody.push(nexthead);
    drawSnakeyellowBody(nexthead.r,nexthead.c);
    board[nexthead.r][nexthead.c] = 1;
}
//the end of the game:-
void GameOver()
{
string sound = "277403__landlucky__game-over-sfx-and-voice.wav";

    isgameover = true;
    PlaySound(sound.c_str(),NULL,SND_ASYNC);
    setcolor(COLOR(255,0,0));
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,6);
    outtextxy(getmaxx()/2,getmaxy()/2, "Game Over");
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
    scoreshownn();

}
//

void moveSnake()
{
    location nexthead = getnexthead();
    switch(board[nexthead.r][nexthead.c])
    {
    case EMPTY:
        moveSnaketonextlocation(nexthead);
        break;

    case APPLE:

        moveandgrawsnake(nexthead);
        moveandgrawgreensnake(nexthead);
        //generatenextapple();
      //eatvoise();
      generatenextredapple();

        //gametrack();

        break;
    case REDAPPLE:

        moveandgrawredsnake(nexthead);
        moveandgrawredsnake(nexthead);
        //generatenextredapple();
        //eatvoise();
       // gametrack();
        generatenextbanana();
        break;
    case PANANA:

        moveandgrawsnake(nexthead);
        moveandgrawyellowsnake(nexthead);
       // gametrack();
        //generatenextbanana();
        //eatvoise();
        gametrack();
        generatenextapple();
        break;


    case WALL:
    case BODY:
        GameOver();
        break;
    }

}
void changeSnakeDirections(char dir)
{
    switch(dir)
    {
    case KEY_UP:
        snakeDirection =UP;
        break;
    case KEY_LEFT:
        snakeDirection =LEFT;
        break;
    case KEY_DOWN:
        snakeDirection =DOWN;
        break;
    case KEY_RIGHT:
        snakeDirection =RIGHT;
        break;
    }
}

void startFire()
{
    FireStarted = true;
    fireLocation = getnexthead();
    fireDirection = snakeDirection;
    drawFire(fireLocation.r,fireLocation.c);
}
void stopFire()
{
    FireStarted = false;
    eraseFire(fireLocation.r,fireLocation.c);
}
void moveFire()
{
    if(FireStarted)
    {
        location nextFireLoc = getNextFireLocation();
        if (nextFireLoc.r >35 || nextFireLoc.r < 0 || nextFireLoc.c >35 || nextFireLoc.c <0)
        {
            stopFire();
            return;
        }
        drawFire(nextFireLoc.r,nextFireLoc.c);
        eraseFire(fireLocation.r,fireLocation.c);
        fireLocation = nextFireLoc;
    }
}

void checkKeyInput()
{
    char dir;
    if(kbhit())
    {
        dir = getch();
        if(dir == 0)
        {
            dir = getch();
            changeSnakeDirections(dir);
        }
        else if(dir == 32) //speacbar is pressed
        {
            if(!FireStarted)
                startFire();
        }
    }
}
int main()
{
    DStart();
    isgameover = false;
    initwindow(630,648);
    initSnake();
    gametrack();
    drawBoard();
//inimate the snake

    int gameTimer = 0;
    while(! isgameover)
    {
        if(gameTimer == INT_MAX)

            gameTimer = 0;
        if(gameTimer % 1000000 == 0 )
            moveFire();
        if(gameTimer % 5000000 == 0)
{
            moveSnake();
            scoreshown();
        }

        //counterscore();

        gameTimer++;
        checkKeyInput();
    }

    while(! kbhit());
    return 0;
}
