#include <stdio.h>
#include <stdlib.h>
#include "game.c"


element* generate(char board[8][8],int color)
{
	arrType moves=init();
	move r={.pos1=0,.pos2=0};
	element* head = malloc(sizeof(element));
	*head = (element){ .ruch = r,.nastepny = NULL };
	move ruch={.pos1=-1,.pos2=-1};
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((board[i][j] == 'n'&& color==0) || (board[i][j] == 'N' && color==1))//skoczki
			{
				for (int k = 0; k < 8; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[0][k]};
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((board[i][j] == 'P' && color))//biale pionki
			{
				for (int k = 0; k < 4; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[1][k]};
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
			}
		}
	}
	return head;
}

void main()
{
	//char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	char board[8][8] = { "n#######","##N#####","########","########","########","###w##n#","###P#k##","#K######"};
	move x={.pos1=56,.pos2=64};
	drawBoard(board);
	element *head = malloc(sizeof(element));
	head = generate(board,1);

	showL(head->nastepny);
	zniszcz(head);
	//printf("%d\n",ifLegal(0,x,board));
	
}
