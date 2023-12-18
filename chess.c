#include <stdio.h>
#include <stdlib.h>
#include "game.c"



move engine(set game,int color,int d)//d glebokosc, wywolywac od parzysstych 
{
	int best=0;
	element *head = malloc(sizeof(element));
	head = generate(game,color);
	while(head)
	{
		move temp=head->ruch;
		char copyBoard[8][8];
        strcpy(copyBoard,game.board);
        copyBoard[digi(temp.pos2,0)][digi(temp.pos2,1)] = game.board[digi(temp.pos1,0)][digi(temp.pos1,1)]; // stadardowy ruch
        copyBoard[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#'; 
	}
}

void main()
{
	//char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	char board[8][8] = { "##b#k###","########","########","#####Pp#","########","#######K","########","########"};
	move x={.pos1=74,.pos2=72};
	set game=setInit(board);
	drawBoard(game.board);
	//printf("%d\n",ifCastle(game.board,1,x));
	//drawBoard(game.board);
	element *head = malloc(sizeof(element));
	head = generate(game,1);
	showL(head->nastepny);
	zniszcz(head);
}
