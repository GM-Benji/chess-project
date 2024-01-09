#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.c"



typedef struct bestReturn {
    move x;
    int value;
}bestReturn;
bestReturn engine(set game,int color,int d)//d glebokosc
{
	bestReturn best;
	bestReturn current;
	current.value=0;
	best.value=0;
	element *head = malloc(sizeof(element));
	//printf("%d \n",d);
	head = generate(game,color);
	if(!head->nastepny)
	{
	    if(isCheck(game.board,!color))
	    {
	        if(color)//biale matuja czarnego
	        {
	            best.x.pos1=1000;
	            best.x.pos2=1000;
	            best.value=1000;
	            return best;
	        }
	    }
		else if(isCheck(game.board,color))//czarne matuja bialego
				{
					if(!color)
					{
					best.x.pos1=-1000;
	                best.x.pos2=-1000;
	                return best;
					}
				}
	    else//pat
	    {
	        best.x.pos1=100;
	        best.x.pos2=100;
			best.value=0;
	        return best;
	    }
	}
	head=head->nastepny;
	best.x=head->ruch;
	//showL(head);
	for(;head;head=head->nastepny)
	{
		
		move temp=head->ruch;
		char rev1=game.board[digi(temp.pos2,0)][digi(temp.pos2,1)];
        game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = game.board[digi(temp.pos1,0)][digi(temp.pos1,1)]; // stadardowy ruch
        game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#'; 
        element *head2 = malloc(sizeof(element));  
	    head2 = generate(game,!color);
		//showL(head2->nastepny);
		if(head2->nastepny==NULL)
	        {
				//printf("%d ",d);
	            if(isCheck(game.board,!color))
	            {
	                if(color)//biale matuja czarnego
	                {
	                    best.x.pos1=1000;
	                    best.x.pos2=1000;
	                    return best;
	                }//czarne matuja bialego
	            }
				else if(isCheck(game.board,color))
				{
					if(!color)
					{
					best.x.pos1=-1000;
	                best.x.pos2=-1000;
	                return best;
					}
				}
	            else//pat
	            {
	                best.x.pos1=100;
	                best.x.pos2=100;
					best.value=0;
	                return best;
	            }
	        }
		head2=head2->nastepny;
		current.x=temp;
	    for(;head2;head2=head2->nastepny)
	    {
		move temp2=head2->ruch;
		//printf("%d %d\n",temp.pos1,temp.pos2);
		char rev=game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];
		game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)]; // stadardowy ruch
        game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = '#'; 
		drawBoard(game.board);
	    if(d)
		{
			bestReturn t=engine(game,color,--d);
			if(current.value<t.value && !color)
			{
				current.value=t.value;
			}
			if(current.value>t.value && color)
			{
				current.value=t.value;
			}
		}
        else 
		{
			int tempValue=evaluate(game.board);
			if(current.value<tempValue && !color)
			{
				current.value=tempValue;
			}
			if(current.value>tempValue && color)
			{
				current.value=tempValue;
			}
		}
		game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];//cofniecie posuniecia
		game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = rev; 
		}
		game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = game.board[digi(temp.pos2,0)][digi(temp.pos2,1)];//cofniecie posuniecia
		game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = rev1;
	   //printf("## %d %d %d\n",current.x.pos1,current.x.pos2,current.value);
	   if(current.value>best.value && color) best=current;
       if(current.value<best.value && !color) best=current;
       zniszcz(&head2);
	}
	zniszcz(&head);
	//printf("%d %d %d\n",best.x.pos1,best.x.pos2,best.value);
	return best;
}
void main()
{
	//char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	char board[8][8] = { "####k###","##q#####","########","########","#####R##","#######K","########","########"};
	set game=setInit(board);
	drawBoard(game.board);
	move x={.pos1=12,.pos2=15};
	bestReturn y=engine(game,0,4);
	printf("%d %d %d\n",y.x.pos1,y.x.pos2,y.value);
	/*element *head =generate(game,0);
	showL(head);
	zniszcz(head);*/
	//printf("%d\n",ifLegal(0,x,game.board));
	
}
