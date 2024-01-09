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
	        }//czarne matuja bialego
	        best.x.pos1=-1000;
	        best.x.pos2=-1000;
	        best.value=-1000;
	        return best;
	        
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
        game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = game.board[digi(temp.pos1,0)][digi(temp.pos1,1)]; // stadardowy ruch
        game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#'; 
        element *head2 = malloc(sizeof(element));  
	    head2 = generate(game,!color);
		if(!head2->nastepny)
	        {
	            if(isCheck(game.board,!color))
	            {
	                if(color)//biale matuja czarnego
	                {
	                    best.x.pos1=1000;
	                    best.x.pos2=1000;
	                    return best;
	                }//czarne matuja bialego
	                best.x.pos1=-1000;
	                best.x.pos2=-1000;
	                return best;
	        
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
		game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)]; // stadardowy ruch
        game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = '#'; 
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
        
	
	   }
	   if(current.value>best.value && color) best=current;
       if(current.value<best.value && !color) best=current;
       zniszcz(&head2);
	}
	zniszcz(&head);
	
	return best;
}
void main()
{
	//char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	char board[8][8] = { "##b#k###","########","R#######","########","########","########","########","#######K"};
	move x={.pos1=74,.pos2=72};
	set game=setInit(board);
	drawBoard(game.board);
	printf("helloworld");
	bestReturn y=engine(game,0,2);
	printf("%d %d\n",y.x.pos1,y.x.pos2);
	//printf("%d\n",ifCastle(game.board,1,x));
	//drawBoard(game.board);
	/*element *head = malloc(sizeof(element));
	head = generate(game,1);
	showL(head->nastepny);
	zniszcz(head);*/
}
