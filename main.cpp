#pragma once
#include <iostream>
#include <conio.h>
#include "AI.cpp"
#include "Ships.cpp"
#include "Board.cpp"

using namespace std;

int enterX()
{
    int x;
    do
    {
        cout << "Enter X cordinate(0-9): ";
        cin >> x;
    } while (x < 0 || x > 9);
    return ++x;
}

int enterY()
{
    int y;
    do
    {
        cout << "Enter Y cordinate(0-9): ";
        cin >> y;
    } while (y < 0 || y > 9);
    return ++y;
}

//O - ship,X - hit, M - miss
int main()
{
    //creating boards begin the game for player and AI
    //Own - plansza gracza z jego statkami, tutaj strzela bot,enemy plansza ai tutaj strzela gracz,ai rozmieszczenie statkow bota
    Board PlayerBoardOwn = Board(), PlayerBoardEnemy = Board(), AIBoard = Board();
    cout << "Game is loading: " << endl;
    AI SI = AI(&AIBoard);
    AI Player = AI(&PlayerBoardOwn);

    int AISscore = 0, PlayerScore = 0;

    while (AISscore < 20 || PlayerScore < 20)
    {

        cout << "-=YOUR SCORE: "<<PlayerScore<<"=-  -=OPPONENT SCORE: "<<AISscore<< "=-"<<endl;
        cout << "==YOUR BOARD==" << endl;
        PlayerBoardOwn.Drawboard();
        cout << "==SI BOARD==" << endl;
        PlayerBoardEnemy.Drawboard();
        int x =enterX();
        int y=enterY();
        if (AIBoard.boardtab[y][x]=='O')//if hit 
        {

            PlayerScore++;
            PlayerBoardEnemy.boardtab[y][x] = 'X';
          
        }
        else if(PlayerBoardEnemy.boardtab[y][x] != 'X')
        {
            PlayerBoardEnemy.boardtab[y][x] = 'M';
        }
        
        SI.shotingsystem(&PlayerBoardOwn,AISscore);

        

        system("cls");
    }
    

    if (AISscore == 10)
        cout << "Game Over";
    else
        cout<<"WIN";


    return 0;

}