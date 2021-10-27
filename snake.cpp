#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
int x, y, tX[100], tY[100], nTail, fruitX, fruitY, score;
enum direction{STOP, UP, DOWN, LEFT, RIGHT};
direction dir;

// playfield
const int width = 20;       
const int height = 30;

void setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;      
    y = height / 2;
    nTail = 0;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw(){
    system("cls"); //refresh screen

    // iX, iY = coordinates (x, y)
    for(int iY = 0; iY < height + 1; iY++){
        for(int iX = 0; iX < width + 1; iX++){
            // border
            if(iY == 0 || iY == height || iX == 0 || iX == width) cout << "#";

            //other stuffs
            else if(fruitX == iX && fruitY == iY) cout << "@"; // fruit
            else if(x == iX && y == iY) cout << "O"; // snake
            else{
                int printed = false;
                for(int i = 0; i < nTail; i++){
                    if(tX[i] == iX && tY[i] == iY){
                        cout << "o";
                        printed = true;
                    }
                }
                if(!printed) cout << " ";
            }
        }
        cout << endl;
    }
    //score
    cout << "Scores: " << score << endl;
}

void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'w': 
                dir = UP;
                break;
            case 's': 
                dir = DOWN;
                break;
            case 'a': 
                dir = LEFT;
                break;
            case 'd': 
                dir = RIGHT;
                break;
            case 'x': 
                gameOver = true;
                break;
        }
    }
}

void logic(){
    int memX = x; //gets current head position before moving
    int memY = y;
    int mem2X, mem2Y;

    switch(dir){
        case UP: 
            y--;
            break;
        case DOWN: 
            y++;
            break;
        case LEFT: 
            x--;
            break;
        case RIGHT: 
            x++;
            break;
    }

    for(int i = 0; i < nTail; i++){
        mem2X = tX[i];
        mem2Y = tY[i];
        tX[i] = memX;
        tY[i] = memY;
        memX = mem2X;
        memY = mem2Y;
    }
    
    for(int i = 0; i < nTail; i++){
        if(x == tX[i] && y == tY[i]) gameOver = true;
    }
    if(x == 0 || x == width + 1 || y == 0 || y == height + 1) gameOver = true; //hits border
    if(x == fruitX && y == fruitY){ //eats fruit
        fruitX = rand() % width;
        fruitY = rand() % height;

        nTail++;
        score += 10;
    }
}

int main(){
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
        Sleep(50);
    }
    system("cls");
    cout << "GAMEOVER\n\nScores: " << score << endl;

    return 0;
}