#include <stdio.h> // czy szach, czy jest cos pomiedzy to do // potem roszady bicie przelot, ruch pionka o dwa pola
#include <stdlib.h>

#include "funkcje.c"
#include "inicjalizacja-ruchow.c"
#include "lista.c"
#include "ocena-pozycji.c"

//starting board arrangement
char board[8][8] = {
    { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
    { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
    { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
};

void drawBoard(char board[8][8])
{
    for(int i=0; i < 8; i++)
    {
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d", 8-i);
        for(int j=0; j<8; j++)
        {
            if(j!=0)
                printf(" ");
            printf("| ");
            if(board[i][j] != '#')
                printf("%c", board[i][j]);
            else
                printf(" ");
        }

        printf(" | \n");
    }
    printf(" +---+---+---+---+---+---+---+---+\n");
    printf("   A   B   C   D   E   F   G   H\n");
}

int gameOver(char board[8][8]) //do zrobienia w innym pliku bo z tego beda korzystac inne funkcje
{
    return 0;
}

move typeMove() //trzeba jeszcze dorobić żeby pobierało info z funkcji sprawdzającej czy ruch jest możliwy do wykonania
{
    char kolumny[8] = {'a','b','c','d','e','f','g','h'}; //tablice pomocnicze do porownania z inputem
    char wiersze[8] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    move conv; //na to skonwertowane
    conv.pos1 = NULL;
    conv.pos2 = NULL;

    printf("    it's your turn to make a move\n");

    int isInputOk; //zmienna ktora pomoga sprawdzic czy input jest poprawnie wpisany
    do
    {
        char takeMove[5];
        printf("(np. g8-f6) >> ");
        scanf("%s", takeMove);

        int isOkey0=0;
        int isOkey1=0;
        int isOkey3=0;
        int isOkey4=0;

        for(int i=0; i<8 && (isOkey0 == 0 || isOkey1 == 0 || isOkey3 == 0 || isOkey4 == 0); i++) //petla leci po calej kolumny i wiersze oraz jezeli wszystko zostalo przekonwertowane poprawnie to wszyskie isOkey zmieniaja sie na 1
        {
            if(takeMove[0] == kolumny[i])
            {
                conv.pos1 += i;
                isOkey0=1;
            }
            if(takeMove[1] == wiersze[i])
            {
                conv.pos1 += i*8;
                isOkey1=1;
            }
            if(takeMove[3] == kolumny[i])
            {
                conv.pos2 += i;
                isOkey3=1;
            }
            if(takeMove[4] == wiersze[i])
            {
                conv.pos2 += i*8;
                isOkey4=1;
            }
        }

        if(isOkey0 == 0 || isOkey1 == 0 || isOkey3 == 0 || isOkey4 == 0) // jezeli cos nie zostalo zmienione to cos zostalo zle wpisane
        {
            printf("invalid input notation\n");
            isInputOk = 0;
        }
        else // jezeli zostalo wpisane dobrze to wypisuje ze teraz sie dzieje analiza planszy, zmienia isInputOk i nie robi petli jeszcze raz
        {
            printf("pricessing the move..\n");
            isInputOk = 1;
        }

        //printf("%d | %d\n", conv.pos1, conv.pos2);
    } while(isInputOk == 0); // jezeli cos nie zostalo zmienione to powtarza wpisywanie

    return conv;
}

int main()
{
    for(int i=0; i<8; i++) //sprawdzacz - to jest niepotrzebne później
    {
        for(int j=0; j<8; j++)
            printf(" %2d", i*8+j);
        printf("\n");
    }
    
    while(gameOver(board)==0)
    {
        drawBoard(board);
        move  playersMove = typeMove();
    }

    if(gameOver(board) == 1) //win
        printf("white wins");
    else if(gameOver(board) == 2) //lose
        printf("black wins");
    else if(gameOver(board) == 3)
        printf("pat / draw"); //draw

    return 0;
}
