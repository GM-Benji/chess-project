#include <stdio.h>
#include <stdlib.h>

//starting board arrangement
char board[8][8] = {
    { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' },
    { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
    { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' }
};

void drawBoard(char board[8][8])
{
    for(int i=0; i < 8; i++)
    {
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d",i+1);
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
    return 1;
}

int main()
{
    while(gameOver(board) != 0) //tu będzie funkcja potrzebna funkcja ktora sprawdza czy jest koniec gry / można przyjąć że 0 to gra w toku, 1 to win, 2 to lose, 3 pat/draw
    {
        drawBoard(board);
        char ruch[5];
        printf("\n ruch (np. g8-f6) >> ");
        scanf("%s", ruch);

        //tu beda wszyskie funkcje dzialjace pokolei w trakcie gry
    }
    if(gameOver(board) == 1) //win
        printf("white wins");
    else if(gameOver(board) == 2) //lose
        printf("black wins");
    else if(gameOver(board) == 3)
        printf("pat / draw"); //draw

    return 0;
}
